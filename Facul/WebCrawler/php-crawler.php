<?php
include "lib/simple_html_dom.php";

class PHPCrawler {
  public $url, $response;
  public $followedLinks = [], $filterRules = [], $filteredLinks = [];
  public $ignoredLinks = [], $analyzedLinks = [];
  private $urlObject;

  function __construct($url) {
    $this->url = $url;
    $this->buildURLObject();
  }

  public function execute() {
    $this->request();
    $this->getLinks();
    $this->filterLinks();
    $this->setIgnoredLinks();
    $this->setAnalyzedLinks();

    // array_map(function($link) {
    //   $this->url = $link;
    //   printf("Trying to parse URL: %s", $this->url);
    //   $this->execute();
    // }, $this->followedLinks);
  }


  public function setURL($url) {
    $this->url = $url;
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

  private function getLinks() {
    $links = array_map(array($this, "extractLink"), $this->response->find("a"));
    $links = array_unique($links);

    $this->followedLinks = array_diff($links, $this->analyzedLinks);
  }

  private function setIgnoredLinks() {
    $this->ignoredLinks = array_values(array_diff($this->followedLinks, $this->filteredLinks));
  }

  private function setAnalyzedLinks() {
    $this->analyzedLinks = array_merge($this->followedLinks, $this->ignoredLinks);
  }

  private function filterLinks() {
    $this->filteredLinks = array_values(array_filter($this->followedLinks, function($link) {
      foreach($this->filterRules as $rule) {
        if (preg_match("/$rule/", $link)) {
          return false;
        }
      }
      return true;
    }));
  }

  private function buildURLObject() {
    $this->urlObject = parse_url($this->url);
  }

  private function request() {
    $this->response = file_get_html($this->url);
  }
}

// nome, preço, foto e descrição dos produtos
//
$crawler = new PHPCrawler("https://www.macbebe.com.br");

echo $crawler->getURL();
$crawler->addFilterRule("^\/$");
$crawler->addFilterRule("javascript:void\(0\)");
$crawler->addFilterRule("^mailto:");
$crawler->addFilterRule("^\/clientes\/");
$crawler->addFilterRule("^\/(atendimento|carrinho|login|cadastrar)");
$crawler->execute();

echo "\n";
print_r($crawler->filteredLinks);
print_r($crawler->ignoredLinks);
?>
