Pi-Box is een project met als idee; een lasdoos met een Pi, relais etc achterin de auto, een hdmi scherm voorin en accessoires gekoppeld aan de lasdoos;

24 Maart 2025:

Het idee dat ik nu heb gaat als volgt:

Ik zal een lasdoos met een Raspberry Pi 3 B+, een 8-relais module en diverse chassis connectoren achterin mijn auto hebben, daaraan een hdmi touch display gekoppeld die voorin de auto op het dashboard gemonteerd zal staan. Op de Pi zal software draaien dat alles met elkaar koppelt, die software zal bestaan uit een controle paneel voor op het touch display waarmee de relais en accessoires te besturen zullen zijn, een webserver voor makkelijke debug/tracking, software log en eventuele remote opties.

Lasdoos:
Ik heb het liefst geen doorgevoerde kabels maar chassis connectoren. Voor de connectoren had ik bedacht dat de accessoires GX16 male/female zullen zijn waardoor de kabels niet permanent zijn maar er mooien kabelharnassen gemaakt kunnen worden, voor het scherm een simpele hdmi connector en eventueel micro usb indien nodig voor het touch display, stroom zal als 12v binnen komen en met een buck converter omgevormd worden naar 5v voor de pi en relais. In de lasdoos zal ook een gps module op de pi aanwezig zijn voor het tracken van locatie, snelheid en mogelijk terug vinden van een gestolen auto. Voor deze laatst benoemde feature zal er extra hardware aanwezig moeten zijn (ik denk een ESP32 vanwege lage idle power usage), dit zal nog veel werk kosten daarom is dit misschien een idee voor een volgende versie (Pi-Box v2??)

Lasdoos inhoud:

Raspberry Pi 3B+,
8-relais module (voorkeur solid state, mechanisch kan ook),
Chassis connectoren,
Debug led'92s voor het snelle inzien van mogelijke error'92s,
GPS module,

Nice to have / volgende versie:
4G module voor draadloze verbinding en mogelijke koppeling met een remote server voor remote control.