#### 4. Cuestionario

####  4.1. ¿Cuáles son los tipos de type descriptors que podemos encontrar en /proc//fd?
  
  Rta:Podemos encontrar 3 tipos de archivos: 
  REG: Archivos regulares. 
  LNK: Enlaces simbólicos (Donde se encuentran pipes y   sockets). 
  CHR: Dispositivos orientados a caracteres. 
  
####  4.2. Suponiendo que un usuario está ejecutando el proceso pid 1212, ¿Es válida la ejecución del siguiente comando desde una terminal nueva? % echo “Hello, world.” >> /proc/1212/fd/1
  
  Rta:La ejecución es válida y lo que hace es redireccionar la salida del comando "echo" hacia la salida estándar del PID 1212. Si ejecuto este comando y puedo ver la salida del PID 1212, la salida del mismo será "Hello, word."
  
####  4.3. Qué diferencia hay entre hard y soft limits?

Rta: Los procesos consumen recursos y el soft limit, limita la cantidad de recursos que el proceso puede consumir. 
El hard limit, es un límite en el valor al que se puede ajustar el soft limit. 
Un proceso sin privilegios puede cambiar su soft limit para un recurso particular a cualquier valor en el rango de cero hasta el hard limit correspondiente, pero solo puede reducir su hard limit. 

NOTA: Honestamente comitié todo el día 13 pero me olvide de responder estas preguntas, se me pasaron por alto, pido disculpas por la demora en esta entrega 
