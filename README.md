+-----------------------------------------------------------------------------+
| ServerProgramm in C                                                         |
+-----------------------------------------------------------------------------+
| Info:
| Keine Anwenenheitspflicht
| Team mit maximal 5 Personen
| Jeder Dokumentiert seinen Teil (Leistungsmatrix)
| Man kann früher abgeben
+-----------------------------------------------------------------------------+
| Ziel:
| Mehrere Cients können sich gleichzeitig verbinden (Port: 5678)
| Server soll Daten speichern/laden/löschen können (Permanent)
| Client kann Daten auf den Server Uploaden und Downloaden, auch löschen.
| Ein Befehlsset (Protokoll) muss verstanden werden.
+-----------------------------------------------------------------------------+

+---[Phase 1]------------------------------------------------------------------+
| Protokoll: [Befehl] [key] [value]
| Keine Sonderzeichen in key oder value
| Key dark keine Leerzeichen haben.
| Man soll Befehle Verketten können. Man erhällt dann aber nur eine Antwort.
|
| Beispiel:
| int Put(char* key, char* value);
| int Get(char* key, char* res);
| int Del(char* key);
+------------------------------------------------------------------------------+
+---[PUT]----------------------------------------------------------------------+
| - Akzeptiert einen key und einen value. 
| - Der Befehl liefert das gespeicherte Paar zurück: 'PUT:key:value'
+---[GET]----------------------------------------------------------------------+
| - Akzeptiert einen key und liefert 'GET:key:value'. 
| - Ist der key unbekannt wird statt dem val ue "key_nonexistent" ausgegeben.
+---[DEL]----------------------------------------------------------------------+
| - Akzeptiert einen key und löscht das Paar aus der Datenhaltung. 
| - War der key vorhanden, wird 'DEL:key:key_deleted' ausgegeben. 
| - War der key nicht vorhanden, wird 'DEL:key:key_nonexistent' ausgegeben
+---[QUIT]---------------------------------------------------------------------+
| - Beendet die Socket Verbindung und terminiert
+---[BEG]----------------------------------------------------------------------+
| - Lock eine Datei (Exclusiver Zugriff)
+---[END]----------------------------------------------------------------------+
| - UnLock eine Datei (Exclusiver Zugriff)
+------------------------------------------------------------------------------+
+---[Example]------------------------------------------------------------------+
| GET key1 
| > GET:key1:key_nonexistent 
| PUT key1 value1 
| > PUT:key1:value1 
| PUT key2 value2 
| > PUT:key2:value2 
| PUT key1 value3 
| > PUT:key1:value3 
| DEL key2 
| > DEL:key2:key_deleted 
| DEL key2 
| > DEL:key2:key_nonexistent 
| GET key1
| > GET:key1:value3 
| QUIT
+-----------------------------------------------------------------------------+


+---[Phase 2]------------------------------------------------------------------+
Achte auch inkonsestente daten (2 clients arbeiten gleichzeitig an etwas)

PUT /SUB
+---[Phase 3]------------------------------------------------------------------+

Führe andere Befehle remote aus
OP

Dokumentation
+-----------------------------------------------------------------------------+
