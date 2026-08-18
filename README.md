<a name="oben"></a>

<div align="center">

|[:skull:ISSUE](https://github.com/frankyhub/RoboCar_AP/issues?q=is%3Aissue)|[:speech_balloon: Forum /Discussion](https://github.com/frankyhub/RoboCar_AP/discussions)|[:grey_question:WiKi](https://github.com/frankyhub/RoboCar_AP/wiki)||
|--|--|--|--|
| | | | |
|![Static Badge](https://img.shields.io/badge/RepoNr.:-%2071-blue)|<a href="https://github.com/frankyhub/RoboCar_AP/issues">![GitHub issues](https://img.shields.io/github/issues/frankyhub/RoboCar_AP)![GitHub closed issues](https://img.shields.io/github/issues-closed/frankyhub/RoboCar_AP)|<a href="https://github.com/frankyhub/RoboCar_AP/discussions">![GitHub Discussions](https://img.shields.io/github/discussions/frankyhub/RoboCar_AP)|<a href="https://github.com/frankyhub/RoboCar_AP/releases">![GitHub release (with filter)](https://img.shields.io/github/v/release/frankyhub/RoboCar_AP)|
|![GitHub Created At](https://img.shields.io/github/created-at/frankyhub/RoboCar_AP)| <a href="https://github.com/frankyhub/RoboCar_AP/pulse" alt="Activity"><img src="https://img.shields.io/github/commit-activity/m/badges/shields" />| <a href="https://github.com/frankyhub/RoboCar_AP/graphs/traffic"><img alt="ViewCount" src="https://views.whatilearened.today/views/github/frankyhub/github-clone-count-badge.svg">  |<a href="https://github.com/frankyhub?tab=stars"> ![GitHub User's stars](https://img.shields.io/github/stars/frankyhub)|
</div>




---


## Story
Diese Anleitung beschreibt den Aufbau eines RoboCars. Der Antrieb des RoboCars erfolgt über vier Getriebe-Motore, als Spannungsversorgung dienen drei 18650 Akkus. Die Träger-Elemente werden aus 4mm Sperrholz- oder ABS-Platten gelasert. Das Herzstück ist ein ESP32 DevKit V4. Die Steuerung des RoboCars erfolgt über einen WEB-Server. Für die Kommunikation zwischen Hamdy/Tablet und den ESP32  wird ein Acces Point verwendet, d.h. es ist kein WLAN nötig. 

In den WLAN-Einstellungen des Handy/Tablet „RoboCar" wählen und den WEB-Server im Browser mit der Adresse 192.168.4.1 starten. 

Mit dem WEB-Server kann das RoboCar vor, zurück rechts und links gesteuert werden. Der Slider dient zur Geschwindigkeitseinstellung des RoboCars im Bereich zwischen 40% und 100%.

Optional kann die Ladung der Akkus über ein Solarpanel erfolgen.



## Hardware

| Stück | Beschreibung | 
| -------- | -------- | 
| 2       | ABS Platten DINA4 4mm oder       | 
| 1        |Sperrholzplatte 600x300x4mm       |
| 1        | ESP32 DevKit V4        | 
| 1         | ESP32-Shield      | 
| 8        | Platinenhalter und Kabelführungen (3D-Druck)        | 
| 4        | Getriebemotore mit Räder       | 
| 1        | Dual-H-Brücke-DC-Motorantrieb L298N        |
| 3      | 18650 Akkus mit Akkucase        | 
|        | Kleinmaterial, Schrauben, Muttern, Klemmen, Platinenstecker, Schaltdraht        | 
| 1      | Laderegler TP4056 (optional)       | 
| 1     | Solar Panel 15w 5V Micro Solar Board 13x15cm (optional)      | 
| 1     | Hartschaumplatte, Polyvinylchlorid (PVC), Solar Panelhalterung (optional)  | 
|    ---    | ---      | 

## Aufbau und Montage

Der Aufbau und die Montage des RoboCars ist in mehrere Schritte unterteilt.

## - Schritt 1: Die Sperrholz-Platten lasern (alternativ eine ABS Platte)
Verwende die Lasercutter Vorlage, bestehend aus:
1 x Deckplatte.svg
1 x Bodenplatte.svg

![Bild](/pic/BM02.png)

## - Schritt 2: Zwölf Platinenhalter und Kabelführungen drucken.
Die Platinenhalter tragen das Akku-Case, den ESP32 und die H-Brücke. Sie werden auf die Bodenplatte geklebt.

![Bild](/pic/3D.png)


## - Schritt 3: Die vier Getriebemotore und den Schalter auf die Grundplatte montieren

![Bild](/pic/RCmontage.png)


## - Schritt 4: Die Bauelemente nach Schaltplan verdrahten.


![Bild](/pic/Schaltplan.png)

![Bild](/pic/RCverdrahtet.png)


## - Schritt 5: Das Programm in den ESP32 laden und auf das Shield stecken.

![Bild](/pic/RoboCar.png) 

## - Schritt 6: In den WLAN Einstellungen des Handys/Tablet das "RoboCar" wählen und im Browser den WEB-Server mit der IP 192.168.4.1 aufrufen.

 
![Bild](/pic/wlan.png) 

![Bild](/pic/RoboBrowser.png)

![Bild](/pic/SeriellerMonitor.png)


## - Schritt 7: Optional können die Akkus über ein Solarpanel geladen werden. Als Laderegler dient ein TP4056.

  
![Bild](/pic/TP4056.png)

![Bild](/pic/Solarpanel.png)

## - Schritt 8: Die Ladeschaltung verdrahten.

![Bild](/pic/Laderegler1.png)

## RoboCar mit Solarpanel, Laderegler und Schalter.

![Bild](/pic/RCsolar.png)

  
## - Fertig!

  Das RoboCar ist vor, zurück, stopp, rechts und links mit dem WEB-Server steuerbar. Die Geschwindigkeits-
  steuerung des RoboCars ist mit einem Slider im WEB-Server in 10er Schritten einstellbar.
  Der WEB-Server ist über den Accses Point direkt mit dem ESP32 verbunden, deshalb ist kein WLAN erforderlich und das RoboCar ist ortsunabhängig. 
  Optional können die drei 18650 Akkus über ein Soloarpanel geladen werden.

  Viel Spaß beim racen! 





---

<div style="position:absolute; left:2cm; ">   
<ol class="breadcrumb" style="border-top: 2px solid black;border-bottom:2px solid black; height: 45px; width: 900px;"> <p align="center"><a href="#oben">nach oben</a></p></ol>
</div>  

---
