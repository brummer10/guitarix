;;
;; Given a uref, returns the device associated nets(s) ordered by their pin#, 
;; what when not defined?
;;      problem is slotted components e.g. ../examples/singlenet_1.sch
;;
(define ampsim:write-net-name-of-component
  (lambda (uref number-of-pin port)
    (if (> number-of-pin 0)
      (begin                                   
            ;; first find pin1 and then start writing the connected net name
        (ampsim:write-net-name-of-component uref (- number-of-pin 1) port)
            ;; generate a pin-name e.g. pin1, pin2, pin3 ...
        (let ((pin-name (number->string number-of-pin)))  
          (display (car (gnetlist:get-nets uref (gnetlist:get-attribute-by-pinseq uref pin-name "pinnumber"))) port)
          (write-char #\space port))))))


;;
;; Given a uref, returns the device attribute value as string
;;
(define ampsim:component-value
  (lambda (package) 
    (let ((value (gnetlist:get-package-attribute package "value"))) 
      (if (not (string=? value "unknown"))
        value
        "None"))))


;;
;; write the uref, the net name connected to pin# and the component value. No extra attributes.
;;
(define ampsim:write-one-component
  (lambda (package port)
    (display (string-append package " ") port) 
    (display (string-append (get-device package) " ") port)
    (display (string-append (ampsim:component-value package) " ") port)
    (ampsim:write-net-name-of-component package (length (gnetlist:get-pins package)) port)))


;;
;; write the uref, to the pin# connected net and component value and optional extra attributes
;; check if the component is a special spice component
;;
(define ampsim:write-netlist
  (lambda (port ls)
     (if (not (null? ls))
      (let ((package (car ls)))                           ;; search for specific device labels
	(ampsim:write-one-component package port)
	(newline port)
        (ampsim:write-netlist port (cdr ls)) ))))  


;;
;; ampsim netlist generation
;;
(define ampsim
  (lambda (output-filename)
    (let ((port (open-output-file output-filename)))
      (ampsim:write-netlist port packages)
      (close-output-port port))))
