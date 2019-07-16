(ns programming-clojure.core
  (:require [programming-clojure.primes :refer :all]
            [programming-clojure.functional :refer :all]
            [clojure.string :as s]))

(defn blank?
  [str]
  (every? #(Character/isWhitespace %) str))

;; Looks like defrecord names a map type (seems an object)
(defrecord Person [first-name last-name])

(def foo (->Person "George" "Jegon"))

(defn hello-world
  [username]
  (println (format "Hello, %s" username)))

;; Accessing map key by keyword match
(hello-world (:first-name foo))

;; Thread-safe, in-memory database of accounts
(def accounts (ref #{}))

(defrecord Account [id balance])

;; Add new map to Account Set, using thread safety
(dosync (alter accounts conj (->Account "CLJ" 1000.00)))

;; Calling methods from Class/instances
(println (s/escape (System/lineSeparator) char-escape-string)) ;; returns => \n
(println (s/escape (. System lineSeparator) char-escape-string)) ;; also returns => \n

;; To access this variable value we can use
;; (deref @accounts) or just @accounts

;; Using Atom for shared state
(def visitors (atom #{}))

;; Add new entry for Visitors Set, using thread safety
(swap! visitors conj "George")

(defn hello
  "Writes hello message to *out*. Calls you by username.
  Knows if you have been here before."
  [username]
  (swap! visitors conj username)
  (str "Hello, " username))

(println (hello "Jegon"))

;; All predicates (which is a function that returns either true or false)
;; always have question mark (?) in the name: true?, false?, zero?
;; to find more predicates use this command:
;; (find-doc #"\?$")

;; Function with different arities
(defn greeting
  "Returns a greeting of the form 'Hello, username.'
  Default username is 'world'."
  ([] (greeting "world"))
  ([username] (str "Hello, " username)))

(println (greeting))

;; Function with optional arguments (variable arity)
(defn date
  [person-1 person-2 & chaperones]
  (println person-1 "and" person-2
           "went out with" (count chaperones) "chaperones."))

(date "Romeo" "Juliet" "Friar Lawrence" "Nurse")

;; Var binding
(def foo 10)
;; Print some var symbol
(println foo)
; Var function refers directly to a variable
(println (var foo))

;; Destructuring

;; Bad Example
(defn greet-author-1 [author]
  (println "Hello," (:first-name author)))

(greet-author-1 {:first-name "Jegon" :last-name "George"})

;; Good Example
(defn greet-author-2 [{fname :first-name}]
  (println "Hello," fname))

(greet-author-2 {:first-name "Abdul" :last-name "George"})

(defn destructuring-test [[_ last-name]]
  (println "Something to say" last-name))

(destructuring-test ["George" "Jegon"])

(defn destructuring-keeping-original [[x y :as full-name]]
  (println "Hello" x "how are" y "full name:" full-name))

(destructuring-keeping-original ["Any" "Name" "Here"])

;; Clojure core functions are in clojure.core namespace
;; to use it just type (clojure.core/use 'clojure.core)

;; Metadata
;(println (meta #'str))

;; Creating function with metadata
;(defn ^{:tag String} shout [^{:tag String} s]
;  (clojure.string/upper-case s))

;; Shorter Form
;(defn ^String shout [^String s]
;  (clojure.string/upper-case s))

;; Show metadata for some symbol
;;(println (meta #'shout))

;; Sequence (List) Comprehension
(println (for [word ["the" "quick" "brown" "fox"]]
           (format "<p>%s</p>", word)))

;; In sequence comprehension the binding-forms are iterated from the rightmost
;; to the left ones
(println (for [file "ABCDEFGH"
               rank (range 1 9)]
           (format "%c%d" file rank)))

(println (for [rank (range 1 9)
               file "ABCDEFGH"]
           (format "%c%d" file rank)))

;; Lazy and Infinite Sequences
(def ordinals-and-primes (map vector (iterate inc 1) primes))
(println (take 5 (drop 1000 ordinals-and-primes)))

;; Seq-ing Java Collections
; String.getBytes returns a byte array
(println (first (.getBytes "hello")))
(println (rest (.getBytes "hello")))
(println (cons (int \h) (.getBytes "ello")))

;; Even or Odd number?
;; As these two function consume stack frames proportional to the size of their
;; argument, they will fail with large numbers
(println (map my-even? (range 10)))
(println (map my-odd? (range 10)))

(println (map custom-even? (range 10)))
(println (map custom-odd? (range 10)))
