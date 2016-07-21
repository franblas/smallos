; Assembly functions vvisible from c code level
global outb
global inb

; outb - send a byte to an I/O port
outb:
    mov al, [esp + 8]    ; Move the data to be sent into the al register
    mov dx, [esp + 4]    ; Move the address of the I/O port into the dx register
    out dx, al           ; Send the data to the I/O port
    ret                  ; Return to the calling function

; inb - read a byte from an I/O port
inb:
    mov dx, [esp+4] ; the port to read from
    in  al, dx      ; reads a byte from dx into al
    ret             ; returns the read byte
