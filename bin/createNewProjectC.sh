 if [ -z "$1" ]; then
    # Falls kein Argument übergeben wurde, den Benutzer zur Eingabe auffordern
    read -p "Bitte geben Sie einen Projektnamen ein: " project_name
  else
    # Projektname aus dem Argument übernehmen
    project_name=$1
  fi


./createGenericProject.sh --c $project_name