#lang plait


(define-type-alias (Stream 'a) (-> (StreamData 'a)))

(define-type (StreamData 'a)
  (sempty)
  (scons [head : 'a] [tail : (Stream 'a)]))





(define (valid-pos? i board)
  (local
    [(define (valid-it i j k board)
       (type-case (Listof Number) board
         [empty #t]
         [(cons x board)
          (and (not (= i x))
               (not (= j x))
               (not (= k x))
               (valid-it (- i 1) j (+ k 1) board))]))]
    (valid-it (- i 1) i (+ i 1) board)))









(define (sappend xs ys)
  (if (sempty? (xs))
      ys
      (lambda()
        (scons (scons-head (xs)) (sappend (scons-tail (xs)) ys)))))



(define (sconcat xs)
  (if (sempty? (xs))
      (lambda () (sempty))
      (sappend (scons-head (xs)) (sconcat (scons-tail (xs))))))


(define (build-stream n foo)
  [local
    [(define (iter t)
      (if (= t n)
          (lambda() (sempty))
          (lambda() (scons (foo t) (iter (+ 1 t))))
      ))]
  (iter 0)])


(define (queens n)
  (local
    [(define (queens-it board left)
       (if (= left 0)
           (lambda () (scons board (lambda () (sempty) )))
           (sconcat (build-stream n (lambda (i)
                                      (if (valid-pos? i board)
                                          (queens-it (cons i board) (- left 1))
                                          (lambda() (sempty))
                                          ))))))]
    (queens-it '() n)))






((queens 4))

((scons-tail ((queens 4))))






