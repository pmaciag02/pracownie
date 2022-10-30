#lang racket

; Wynik działania parsera. Jeśli parsowanie się powiedzie,
; to zwracana jest następująca struktura zawierająca wyniki
; oraz nieskonsumowane tokeny. Jeśli parsowanie się nie
; powiedzie, zwracana jest wartość #f.
(struct parse-ok (result rest))

; Wyrażenia opisane produkcją:
;   expr -> simple-expr expr-rest
(define (parse-expr toks)
  (match (parse-simple-expr toks)
    [(parse-ok e1 toks)
     (match (parse-expr-rest toks e1)
       [(parse-ok e2 toks) (parse-ok e2 toks)]
       [#f #f])]
    [#f #f]))

; Wytażenia proste opisane produkcjami:
;  simple-expr -> NUMBER
;  simple-expr -> ( expr )
(define (parse-simple-expr toks)
  (cond
    [(null? toks) #f]
    [(number? (car toks)) (parse-ok (car toks) (cdr toks))]
    [(list? (car toks))
     (match (parse-expr (car toks))
       [(parse-ok e '()) (parse-ok e (cdr toks))]
       [else #f])]
    [else #f]))

; Reszta wyrażenia opisana produkcjami
;  expr-rest -> operator simple-expr expr-rest
;  expr-rest -> {puste}
(define (parse-expr-rest toks val)
  (match (parse-operator toks)
    [(parse-ok op toks)
     (match (parse-simple-expr toks)
       [(parse-ok e2 toks)
        (match (parse-expr-rest toks (op val e2))
          [(parse-ok ans toks)
           (parse-ok ans toks)]
          [#f #f])]
       [#f #f])]
    [#f (parse-ok val toks)]))

; Operator opisany produkcjami:
;  operator -> +
;  operator -> -
(define (parse-operator toks)
  (cond
    [(null? toks) #f]
    [(eq? '+ (car toks)) (parse-ok + (cdr toks))]
    [(eq? '- (car toks)) (parse-ok - (cdr toks))]))

(define (run-expr-parser toks)
  (match (parse-expr toks)
    [(parse-ok e '()) e]
    [else (error "Syntax error")]))
