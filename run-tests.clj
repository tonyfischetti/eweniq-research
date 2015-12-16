#!/opt/local/bin/clj

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;                                        ;;;;;
;;;;;  this is my first clojure script ok?!  ;;;;;
;;;;;                                        ;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(require '[clojure.string :as str])
(require '[clojure.java.shell :as shell])


(def spacing "            ")

(def tests ["testint.txt"
            "somebody.txt"
            "nothing"
            "douglass.txt"
            "of-human-bondage.txt"])

(def test-files (map (fn [post] (str "./test-files/" post)) tests))

(def test-answers (map (fn [post] (str "./test-solutions/" post)) tests))


(def implementations ["./comparisons/simple-bin-tree/driver"
                      "./other-implementations/eweniq-awk.sh"
                      "./other-implementations/eweniq-perl.sh"])


(defn rep-each
  ([vect]
   (rep-each vect 4))
  ([vect n]
   (flatten (map (partial replicate n) vect))))


(defn log! [& args]
  (->> (cons spacing args)
       (str/join "")
       (println)))


(defn construct-test-command [exe test-file]
  (->> (apply str [exe "<" test-file])
       (list)
       (cons "-c")
       (cons "sh")))

(defn construct-perf-command [exe test-file]
  (->> (apply str ["gtime --format 'used %M and took %e' "
                   exe "<" test-file])
       (list)
       (cons "-c")
       (cons "sh")))
       



(defn run-command-get-output
  ([command]
   (run-command-get-output :out command))
  ([stream command]
   (stream (apply shell/sh command))))




; side-effectful
(defn test-executable-with-one-file [exe [test-file test-answer]]
  (log! "about to test file '" test-file "'")
  (let [output (run-command-get-output (construct-test-command exe test-file))
        supposed-to-be (slurp test-answer)]
    (= output supposed-to-be)))


; side-effectful
(defn test-executable [exe]
  (let [tests (map vector test-files test-answers)]
    (log! "using executable '" exe "' for testing")
    (let [rets (map (partial test-executable-with-one-file exe) tests)]
      (if (> (count (filter false? rets)) 0)
        (log! "Tests failed!")
        (log! "Tests passed!"))))
  ; performance
  (let [commands (map (partial construct-perf-command exe) (rep-each test-files))
        output   (map (fn [out] (str/replace out #"\n" ""))
                      (map (partial run-command-get-output :err) commands))
        tups     (map vector (replicate (count commands) exe)
                      (rep-each tests) output)]
    (dorun (map println tups))))


(defn performance [exe]
  (map (partial construct-perf-command exe) test-files))






(defn main []
  (dorun (map test-executable implementations))
  ;; (println (map performance implementations))
  (System/exit 0))



(main)


