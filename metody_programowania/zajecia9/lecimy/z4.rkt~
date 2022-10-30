#lang plait



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



(define-type-alias (Stream 'a) (-> (StreamData 'a)))

(define-type (StreamData 'a)
  (sempty)
  (scons [head : 'a] [tail : (Stream 'a)]))


(define ex1
  (lambda ()(scons '(2 1 3 7) (lambda () (sempty)))))

(define ex2
  (lambda ()(scons '(6 9) (lambda() (scons '(4 2 0) (lambda () (sempty)))))))



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











