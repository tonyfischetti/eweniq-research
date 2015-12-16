#!/opt/local/bin/clj


;;
;; This is to make a block of text a test file
;;


(require '[clojure.string :as str])


(defn main [filename]
  (-> (slurp filename)
      (str/lower-case)
      (str/replace #"\s+" " ")
      (str/replace #"[^a-z ]+" "")
      (str/replace #" " "\n")))


(println (main "./human.txt"))

