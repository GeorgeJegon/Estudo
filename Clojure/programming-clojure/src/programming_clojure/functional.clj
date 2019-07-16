(ns programming-clojure.functional)
(declare my-odd? my-even? my-odd?* my-even?*)

;; bad idea
(defn stack-consuming-fibo [n]
  (cond
    (= 0 n) 0
    (= n 1) 1
    :else (+ (stack-consuming-fibo (- n 1))
             (stack-consuming-fibo (- n 2)))))

;; tail recursion
(defn tail-fibo [n]
  (letfn [(fib
            [current next n]
            (if (zero? n)
              current
              (fib next (+ current next) (dec n))))]
    (fib 0N 1N n)))

;; better but not great
(defn recur-fibo [n]
  (letfn [(fib
            [current next n]
            (if (zero? n)
              current
              (recur next (+ current next) (dec n))))]
    (fib 0N 1N n)))

;; lazy seq
(defn lazy-seq-fibo
  ([]
   (concat [0 1] (lazy-seq-fibo 0N 1N)))
  ([a b]
   (let [n (+ a b)]
     (lazy-seq
       (cons n (lazy-seq-fibo b n))))))

;; better solution
(defn fibo []
  (map first
       (iterate
         (fn [[a b]] [b (+ a b)])
         [0N 1N])))

;; Consumes stack frames -> bad solution
(defn my-odd? [n]
  (if (= 0 n)
    false
    (my-even? (dec n))))

;; Consumes stack frames -> bad solution
(defn my-even? [n]
  (if (= 0 n)
    true
    (my-odd? (dec n))))

;; better solution using bitwise
(defn custom-even? [n] (zero? (bit-and n 1)))
(defn custom-odd? [n] (not (custom-even? n)))

;; Parity function
(defn parity [n]
  (loop [n n par 0]
    (if (= 0 n)
      par
      (recur (dec n) (- 1 par)))))

;; Trampoline
;; Using it we allows trampoline handle function recursion as long the calling
;; function returns another function -> better for mutual recursion
(defn trampoline-fibo [n]
  (let [fib (fn fib [f-2 f-1 current]
              (let [f (+ f-2 f-1)]
                (if (= n current)
                  f
                  #(fib f-1 f (inc current)))))]
    (cond
      (= 0 n) 0
      (= 1 n) 1
      :else (fib 0N 1 2))))

(defn my-even?* [n]
  (if (= 0 n)
    true
    ))
