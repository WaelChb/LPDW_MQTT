# LPDW_MQTT

Guide d'utilisation
1. Configuration des identifiants réseau et MQTT
Modifiez les valeurs des identifiants WiFi (ssid et password) pour correspondre à votre réseau WiFi.
Modifiez les valeurs des identifiants MQTT (mqtt_server, mqtt_port, mqtt_user et mqtt_pwd) pour correspondre à votre serveur MQTT.
2. Installation des bibliothèques requises
Assurez-vous d'avoir installé les bibliothèques PubSubClient et Tomoto_HM330X dans votre environnement Arduino.
3. Connexion au réseau WiFi
Le programme se connectera automatiquement à votre réseau WiFi à l'aide des identifiants fournis.
4. Configuration des messages MQTT
Le programme est configuré pour recevoir des messages sur le sujet MQTT "lpdw".
Lorsque le message reçu est "ON", le capteur HM330X lit les données et publie la valeur PM2.5 sur le sujet MQTT "lpdw".
Lorsque le message reçu est "OFF", le message "LED turned OFF" est publié sur le sujet MQTT "lpdw".
5. Affichage des données
Les données publiées sur le sujet MQTT "lpdw" peuvent être consultées sur votre client MQTT.
6. Gestion des connexions MQTT
Le programme gère automatiquement les connexions et reconnexions au serveur MQTT.
Note importante
Assurez-vous d'avoir correctement câblé et configuré votre capteur HM330X selon les spécifications du fabricant pour garantir des lectures précises.

Ceci est un guide de base pour commencer à utiliser le code. Vous pouvez le personnaliser davantage en fonction de vos besoins spécifiques.