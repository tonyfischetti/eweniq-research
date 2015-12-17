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
            "douglass.txt"
            "of-human-bondage.txt"
            ;; "words.txt"
            ;; "shufwords.txt"
            "nothing"])

(def test-files (map (fn [post] (str "./test-files/" post)) tests))

(def test-answers (map (fn [post] (str "./test-solutions/" post)) tests))


(def all-implementations ["./comparisons/my-simple-bin-tree/eweniq-clang-O0"
                          "./comparisons/my-simple-bin-tree/eweniq-clang-O3"
                          "./comparisons/my-simple-bin-tree/eweniq-gcc-O0"
                          "./comparisons/my-simple-bin-tree/eweniq-gcc-O3"
                          "./comparisons/my-sll-poly-recur/eweniq-clang-O0"
                          "./comparisons/my-sll-poly-recur/eweniq-clang-O3"
                          "./comparisons/my-sll-poly-recur/eweniq-gcc-O0"
                          "./comparisons/my-sll-poly-recur/eweniq-gcc-O3"
                          ;; "./comparisons/my-sll-poly-recur-sent-bad/eweniq-clang-O0"
                          ;; "./comparisons/my-sll-poly-recur-sent-bad/eweniq-clang-O3"
                          ;; "./comparisons/my-sll-poly-recur-sent-bad/eweniq-gcc-O0"
                          ;; "./comparisons/my-sll-poly-recur-sent-bad/eweniq-gcc-O3"
                          ;; "./comparisons/my-sll-poly-recur-sent-good/eweniq-clang-O0"
                          ;; "./comparisons/my-sll-poly-recur-sent-good/eweniq-clang-O3"
                          ;; "./comparisons/my-sll-poly-recur-sent-good/eweniq-gcc-O0"
                          ;; "./comparisons/my-sll-poly-recur-sent-good/eweniq-gcc-O3"
                          ;; "./comparisons/my-sll-nonpoly-recur/eweniq-clang-O0"
                          ;; "./comparisons/my-sll-nonpoly-recur/eweniq-clang-O3"
                          ;; "./comparisons/my-sll-nonpoly-recur/eweniq-gcc-O0"
                          ;; "./comparisons/my-sll-nonpoly-recur/eweniq-gcc-O3"
                          "./comparisons/glib-sll/eweniq-clang-O0"
                          "./comparisons/glib-sll/eweniq-clang-O3"
                          "./comparisons/glib-sll/eweniq-gcc-O0"
                          "./comparisons/glib-sll/eweniq-gcc-O3"
                          "./comparisons/glib-tree/eweniq-clang-O0"
                          "./comparisons/glib-tree/eweniq-clang-O3"
                          "./comparisons/glib-tree/eweniq-gcc-O0"
                          "./comparisons/glib-tree/eweniq-gcc-O3"
                          "./other-implementations/eweniq-awk.sh"
                          "./other-implementations/eweniq-perl.sh"])

(def implementations 
  (filter (fn [s] (and (re-find #"O3" s) (re-find #"gcc" s))) all-implementations))


(def default-reps 20)


(defn rep-each
  ([vect]
   (rep-each vect default-reps))
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


