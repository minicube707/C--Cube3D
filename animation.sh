#!/bin/bash
# Fonction spinner
animation() {
    local delay=0.1     # Délai pour l'animation (vitesse du spinner)

    echo " _____________________________________________"
    sleep $delay
    echo "|.'',                                     ,''.|"
    sleep $delay
    echo "|.'.'',                                 ,''.'.|"
    sleep $delay
    echo "|.'.'.'',                             ,''.'.'.|"
    sleep $delay
    echo "|.'.'.'.'',                         ,''.'.'.'.|"
    sleep $delay
    echo "|.'.'.'.'.|                         |.'.'.'.'.|"
    sleep $delay
    echo "|.'.'.'.'.|===;                 ;===|.'.'.'.'.|"
    sleep $delay
    echo "|.'.'.'.'.|:::|',             ,'|:::|.'.'.'.'.|" 
    sleep $delay
    echo "|.'.'.'.'.|---|'.|, _______ ,|.'|---|.'.'.'.'.|"
    sleep $delay
    echo "|.'.'.'.'.|:::|'.|'|???????|'|.'|:::|.'.'.'.'.|"
    sleep $delay
    echo "|,',',',',|---|',|'|???????|'|,'|---|,',',',',|"
    sleep $delay
    echo "|.'.'.'.'.|:::|'.|'|???????|'|.'|:::|.'.'.'.'.|"
    sleep $delay
    echo "|.'.'.'.'.|---|','   /%%%\   ','|---|.'.'.'.'.|"
    sleep $delay
    echo "|.'.'.'.'.|===:'    /%%%%%\    ':===|.'.'.'.'.|"
    sleep $delay
    echo "|.'.'.'.'.|%%%%%%%%%%%%%%%%%%%%%%%%%|.'.'.'.'.|"
    sleep $delay
    echo "|.'.'.'.','       /%%%%%%%%%\       ','.'.'.'.|" 
    sleep $delay
    echo "|.'.'.','        /%%%%%%%%%%%\        ','.'.'.|"
    sleep $delay
    echo "|.'.','         /%%%%%%%%%%%%%\         ','.'.|"
    sleep $delay
    echo "|.','          /%%%%%%%%%%%%%%%\          ','.|"
    sleep $delay
    echo "|;____________/%%%%%Spicer%%%%%%\____________;|"
    
}

# Simuler un processus en arrière-plan (par exemple, un `sleep` long)
sleep 10 & pid=$!  # Lance un processus `sleep 10` en arrière-plan, récupère son PID
animation "$pid"   # Passe ce PID au spinner


