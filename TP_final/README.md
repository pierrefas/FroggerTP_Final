    Para generar el ejecutable del TP_final es necesario compilar con el flag FORCE_ALLEGRO=yes 
    ya que sino no se compilaran los archivos a_ ni tampoco se agregaran las librerias de Allegro 
    ( font, image, primitive etc...)

    para simplicidad aca dejo el bash para copiar y compilar mas facilmente:

    make TP_final FORCE_ALLEGRO=yes

    aparte de esto es fundamental hacer un make clean entre versiones (raspi a PC y biceversa)
    para que no se acumulen los codigos objetos y dependencias de las respectivas versiones