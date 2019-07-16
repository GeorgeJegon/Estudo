(ns programming-clojure.state-and-concurrency)

;; Creates a def var assingment that reference to this String value
(def current-track (ref "Mars, the Bringer of War"))
;; We can access this var value using 'deref function or @ macro
(println (deref current-track))

;; ref-set function
;; change the value where reference points to
;; as refs are mutable, we must protect their updates with dosync function
(dosync (ref-set current-track "Venus, the Bringer of Peace"))
(println @current-track)

;; Clojure has STM (Software Transactional Memory) that allows us to use
;; ACI (atomic, consistent and isolated) - kind of database's ACID but without
;; durable one (as Clojure use local memory)

(def current-composer (ref "Holst"))
(println {:current-track @current-track :current-composer @current-composer})

;; Using dosync function we gain some transaction bonus and atomicity updates
(dosync
  (ref-set current-track "Credo")
  (ref-set current-composer "Byrd"))
(println {:current-track @current-track :current-composer @current-composer})

;; Alter function
;; Usefull when we do not need to be concerned about the previous ref state

(defrecord Message [sender text])
(->Message "Aaron" "Hello")
(def messages (ref ()))

(defn add-message [msg]
  (dosync (alter messages conj msg)))

(add-message (->Message "user 1" "hello"))
(add-message (->Message "user 2" "howdy"))
(println @messages)

;; Adding Validation to Refs
(defn valid-message? [msg]
  (and (:sender msg) (:text msg)))

(def validate-message-list #(every? valid-message? %))
(def messages (ref () :validator validate-message-list))

;; (add-message "XPTO") => throws an exception


;; Use Atoms for Uncoordinated, Synchronous Updates
(def current-track (atom "Venus, the Bringer of Peace"))
(println @current-track)

(reset! current-track "Credo")
(println @current-track)

(def current-track (atom {:title "Credo" :composer "Byrd"}))
(reset! current-track {:title "Spem in Alium" :composer "Tallis"})

(swap! current-track assoc :title "Sancte Deus")
(println @current-track)

;; Use Agents for Asynchronous Updates
(def counter (agent 0))
(send counter inc)
(println @counter)

;; We can use await and await-for function to wait until the agente finish its job
;; blocking the thread :D

;; Validating Agents and Handling Errors
(def counter (agent 0 :validator number?))
(send counter (fn [_] "boo"))
;;(println (agent-error counter)) => returns an error

;; Including Agents in Transactions
(def backup-agent (agent "output/messages-backup.clj"))
(defn add-message-with-backup [msg]
  (dosync
    (let [snapshot (commute messages conj msg)]
      (send-off backup-agent (fn [filename]
                               (spit filename snapshot)
                               filename))
      snapshot)))

(add-message-with-backup (->Message "John" "Message One"))
(add-message-with-backup (->Message "Jane" "Message Two"))