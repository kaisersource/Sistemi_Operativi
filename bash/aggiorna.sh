 #!/bin/bash 


read -p "inserisci cartella sorgente " s1      #lettura da tastiera successiva all'output
read -p "inserisci cartella destinazione " s2


    if [ -h  "$s1" ] || [ -h "$s2" ]; then #verifica se le dir sono link simbolici
	echo "link simbolici" && exit 1;       #stamp
        
       elif [ ! -d "$s1" ] || [ ! -d "$s2" ] ; then  #1st --  verifica l' identita e l'esistenza della directory
       echo "dir inesistenti o non sono cartelle" && exit 1;
	fi
  for p1 in "$s1/"*; do  # ciclo 
    if [ "$pwd($s2)" = "$pwd($p1)" ]; then #se s2 appartiene alla directory o sottodirectory di s1 
      echo "errore, le directories si trovano sullo stesso ramo" &&  exit 1;
    fi
  done #chiusura primo ciclo
  for p2 in "$s2/"*; do #ciclo nella seconda directory
	if [ "$pwd($s1)" = "$pwd($p2)" ]; then #controlla se la dir $s1 è una subdir 
      echo "errore, le directories si trovano sullo stesso ramo" &&  exit 1;
	fi
			
  done #chiusura secondo ciclo
   
###se i requisiti sono soddisfatti, procedo
     
for p1 in "$s1/"* ; do
	if [ "$(ls -l "$p1" |cut -c -1)" = "-" ] ; then #filtro il risultato di ls -l, restituendomi il char che identifica il tipo di file
			
			if [ "$p1" -nt  "$s2"/"$p1" ] ; then #se true allora p1 piu aggiornato di p1 di s2, altrimenti copio p1 se il file in s2 non esiste
				cp $p1 $s2		               
			fi
			
	fi
done
   
#eof
	
		
	
        
           
      	






	 





	





 
