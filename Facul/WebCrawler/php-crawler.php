<?php
require_once "lib/simple_html_dom.php";
require_once "lib/http_build_url.php";
require_once "lib/parsecsv.lib.php";

// https://stackoverflow.com/questions/13139704/multi-thread-multi-curl-crawler-in-php

class PHPCrawler {
  public $url, $response;
  public $foundLinks = [], $filterRules = [], $filteredLinks = [];
  public $ignoredLinks = [], $analyzedLinks = [];
  private $urlObject;
  private $csv;

  private $filterSameHost = false;

  function __construct($url) {
    date_default_timezone_set("Brazil/East");
    $this->url = $url;
    $this->csv = new parseCSV();
    $this->csv->save("data.csv",[]);
    $this->buildURLObject();
  }

  public function execute() {
    $this->request();
    if (!$this->response) {
      $this->logger(sprintf("Unabled to parse URL: %s", $this->url));
      return false;
    }

    $this->handlePage();

    $this->getLinks();
    $this->filterLinks();
    $this->setIgnoredLinks();
    $this->setAnalyzedLinks();

    array_map(function($link) {
      $this->setURL($link);
      $this->execute();
    }, $this->filteredLinks);
  }

  public function handlePage() {
    $productContent = $this->response->find("[class='content-product']", 0);

    if (is_object($productContent)) {
      $productInfo  = $productContent->find("[class='product-info']", 0);
      $productPhoto = $productContent->find("#ctrFotoPrincipal", 0)->getAttribute("src");
      $productValue = $productInfo->find("span.ctrValorMoeda", 0)->innertext;
      $productName  = trim($productInfo->find("h1[itemprop='name']", 0)->innertext);
      $productDescription = $productContent->find("[data-tab='product-description'] p", 1)->innertext;

      $productRow = array(
        $productName,
        $this->url,
        $productDescription,
        $productValue,
        $productPhoto
      );

      $productRow = array_map("strip_tags", array_map("trim", array_map("html_entity_decode", $productRow)));

      $this->csv->save("data.csv",
        array(
          $productRow
        ),
      true);
    } else {
      $this->logger("Element not found! [Error 404 :D]");
    }
  }

  public function useSameHostFilter() {
    $this->filterSameHost = true;
  }

  public function setURL($url) {
    $this->url = $this->transformRelativeURLtoAbsolute($url);
  }

  public function getURL() {
    return $this->url;
  }

  public function getResponse() {
    return $this->response;
  }

  public function addFilterRule($rule) {
    array_push($this->filterRules, $rule);
  }

  private function extractLink($domElement) {
    return $domElement->getAttribute("href");
  }

  private function request() {
    $this->logger(sprintf("Making request to URL: %s", $this->url));
    $this->response = @file_get_html($this->url);
  }

  private function getLinks() {
    $links = array_map(array($this, "extractLink"), $this->response->find("a"));
    $links = array_unique($links);

    $this->foundLinks = array_diff($links, $this->analyzedLinks);
  }

  private function setIgnoredLinks() {
    $this->ignoredLinks = array_values(array_diff($this->foundLinks, $this->filteredLinks));
  }

  private function setAnalyzedLinks() {
    $this->analyzedLinks = array_merge(
      $this->analyzedLinks,
      array_merge($this->foundLinks, $this->ignoredLinks)
    );
  }

  private function filterLinks() {
    $links = $this->foundLinks;
    $links = array_filter($links, array($this, "applyFilters"));
    $links = array_map(array($this, "transformRelativeURLtoAbsolute"), $links);

    if ($this->filterSameHost) {
      $links = array_filter($links, array($this, "ignoreDifferentHost"));
    }

    $links = array_diff($links, $this->analyzedLinks);

    $this->filteredLinks = array_values($links);
  }

  private function ignoreDifferentHost($link) {
    $urlObject = parse_url($link);

    return $this->urlObject["host"] == $urlObject["host"];
  }

  private function applyFilters($link) {
   foreach($this->filterRules as $rule) {
      if (preg_match("/$rule/", $link)) {
        return false;
      }
    }
    return true;
  }

  private function buildURLObject() {
    $this->urlObject = parse_url($this->url);
  }

  private function transformRelativeURLtoAbsolute($url){
    $url = filter_var($url, FILTER_SANITIZE_URL);
    $is_validURL = filter_var($url, FILTER_VALIDATE_URL);
    $urlObject = parse_url($url);

    if (!$is_validURL) {
      $url = http_build_url(array_merge($this->urlObject, $urlObject));
    }
    return $url;
  }

  private function logger($msg) {
    printf("[%s][PHPCrawler] %s\n", date("Y-m-d H:i:s"), $msg);
  }
}

// nome, preço, foto e descrição dos produtos
$url = "https://www.macbebe.com.br";

$crawler = new PHPCrawler($url);
$crawler->useSameHostFilter(true);
$crawler->addFilterRule("^\/$");
$crawler->addFilterRule("javascript:void\(0\)");
$crawler->addFilterRule("^mailto:");
$crawler->addFilterRule("^\/(clientes|atendimento|carrinho|login|cadastrar)");
$crawler->addFilterRule("http:\/\/www\.(ebit|moovin)\.com\.br");
$crawler->addFilterRule("\?(cor|colecao|tamanho|ordem|idgrade|comtodos|busca)");
$crawler->addFilterRule("\&tamanho");
$crawler->execute();
?>
