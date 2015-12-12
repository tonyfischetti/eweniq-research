#!/opt/local/bin/clj

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;                                        ;;;;;
;;;;;  this is my first clojure script ok?!  ;;;;;
;;;;;                                        ;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(require '[clojure.string :as s])
(use '[clojure.java.shell :only [sh]])


(def spacing "            ")

(def test-files ["./test-files/testint.txt"
                 "./test-files/somebody.txt"
                 "./test-files/nothing"])

(def test-answers ["./test-solutions/testint.txt"
                   "./test-solutions/somebody.txt"
                   "./test-solutions/nothing"])


(defn log! [& args]
  (->> (cons spacing args)
       (s/join "")
       (println)))


(defn construct-command [exe test-file]
  (->> (apply str [exe "<" test-file])
       (list)
       (cons "-c")
       (cons "sh")))


(defn run-command-get-output [command]
  (:out (apply sh command)))


(defn test-executable-with-files [exe [test-file test-answer]]
  (log! "about to test file '" test-file "'")
  (let [output (run-command-get-output (construct-command exe test-file))
        supposed-to-be (slurp test-answer)]
    (= output supposed-to-be)))


(defn main [args]
  (let [exe (first args)
        tests (map vector test-files test-answers)]
    (log! "using executable '" exe "' for testing")
    (let [rets (map (partial test-executable-with-files exe) tests)]
      (if (> (count (filter false? rets)) 0)
        (do (log! "Tests failed!")
            (System/exit 1))
        (do (log! "Tests passed!")
            (System/exit 0))))))



(main *command-line-args*)


