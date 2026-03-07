Titlu Proiect: Modelarea Compromisului dintre Siguranță și Poluare Fonică în Traficul Urban

Slide 1: Introducere și Obiectiv
Ce afișezi: Titlul proiectului sau fereastra de start a simulării (închisă momentan).

Discurs:

"Bună ziua. Pentru proiectul final de modelare și simulare, am ales o temă actuală în ingineria traficului: Siguranța Pietonală în era Vehiculelor Electrice.

Problema pe care o modelez este un compromis fundamental: Pe de o parte, vrem mașini silențioase pentru a reduce poluarea fonică în orașe. Pe de altă parte, liniștea ucide – pietonii nu aud mașinile care se apropie.

Obiectivul simulării mele este să găsesc punctul de echilibru dintre Siguranță (evitarea coliziunilor) și Confort Acustic (nivelul de Annoyance)."

Slide 2: Fundamentarea Științifică (Research-Backed)
Ce afișezi: Codul, zona VEHICLE_TYPES (Liniile 28-65).

Discurs:

"Un aspect cheie al acestui proiect este că nu am folosit valori aleatorii. Parametrii simulării sunt calibrați pe baza a două studii publicate în 2025:

Bazilinskyy et al. (Nature Communications): Acest studiu cuantifică cât de enervante sunt sunetele sintetice (AVAS).

[Arată în cod linia cu 'EV_PURE' annoyance=5.4]: Studiul arată că tonurile pure sunt cele mai deranjante (scor 5.4/10), în timp ce sunetele complexe sunt mai tolerate.

Wadud (Arxiv): Acest studiu aduce un insight surprinzător pe care l-am implementat: Vehiculele Hibride (HEV) sunt implicate în de 2 ori mai multe accidente decât cele clasice, din cauza modului electric la viteze mici și a utilizării intense în regim de taxi.

[Arată în cod linia cu 'HEV' detectability=0.70]: Am modelat acest lucru scăzând detectabilitatea hibridelor, dar am redus și severitatea rănilor (severity_risk=0.05), conform datelor statistice."

Slide 3: Complexitatea Modelului (Extra Points)
Ce afișezi: Clasele Vehicle (metoda update) și Pedestrian (metoda decide_to_cross).

Discurs:

"Pentru a depăși nivelul unei simulări de bază, am implementat mai multe mecanisme complexe de fizică și comportament:

Comportament dual al Pietonilor:

Avem Pietoni Regulamentari (mode='legal'): Aceștia apar doar la trecerea de pietoni și respectă culoarea semaforului.

Avem Jaywalkers (Traversare neregulamentară): Aceștia folosesc un algoritm de Gap Acceptance. Ei estimează viteza mașinii și distanța; dacă devin nerăbdători (impatience), își asumă riscuri mai mari.

Fizica Vehiculelor și Emergency Braking:

Am diferențiat tehnologiile: Mașinile electrice au o eficiență de frânare cu 30% mai mare (brake_efficiency=1.3) datorită frânării regenerative și a răspunsului instantaneu al cuplului motor.

Toate vehiculele scanează activ drumul. Dacă detectează un pieton pe traiectorie, intră în Emergency Braking, simulând sistemele ADAS moderne."

Slide 4: Demonstrație Live - Scenariile
Ce faci: Rulezi codul (python simulation.py). În timp ce rulează, comuți scenariile apăsând tastele 1, 2, 3.

Discurs:

"Voi rula acum simularea, care este împărțită în 3 scenarii narative:

[Apasă tasta 1] Scenariul A: The Silent Danger (Pre-2019) Aici avem un mix de Diesel și EV-uri vechi, fără sunet. Observați că nivelul de Annoyance (afișat pe ecran) este mic (~2.2), dar apar multe Near Misses (situații la limită) și coliziuni, pentru că pietonii nu aud mașinile.

[Apasă tasta 2] Scenariul B: The Hybrid Problem Acest scenariu testează ipoteza lui Wadud. Traficul este 100% Hibrid. Observați o frecvență mare a incidentelor din cauza detectabilității reduse, dar, conform datelor, majoritatea sunt răni ușoare (Minor Injuries), nu severe.

[Apasă tasta 3] Scenariul C: Optimized Future Aici folosim sunete AVAS complexe. Nivelul de zgomot crește (Annoyance ~4.5), dar pietonii detectează mașinile mult mai devreme și așteaptă. Coliziunile scad drastic."

Lasă simularea să ruleze câteva secunde pe Scenariul C pentru a aduna date, apoi închide fereastra Pygame pentru a genera graficul.

Slide 5: Analiza Rezultatelor (Plot-ul Matplotlib)
Ce afișezi: Graficul generat automat la închiderea simulării.

Discurs:

"Graficul generat la final sintetizează rezultatele:

Barele Roșii (Coliziuni): Sunt maxime în Scenariul B (Hibride), confirmând riscul de 2x din studiul lui Wadud.

Barele Portocalii (Near Misses): Aceasta este o metrică de finețe adăugată de mine. Arată de câte ori pietonii și mașinile au trecut la câțiva centimetri unii de alții fără impact. Este indicatorul real al pericolului "invizibil".

Linia Violet (Annoyance): Observăm costul siguranței. În Scenariul C (Future), siguranța este maximă (coliziuni minime), dar linia violet este sus. Acesta este prețul pe care îl plătim auditiv pentru a salva vieți."

Slide 6: Concluzii
Ce afișezi: Graficul sau o pagină de final.

Discurs:

"În concluzie, simularea mea demonstrează că simpla înlocuire a motoarelor termice cu cele electrice aduce riscuri noi.

Soluția optimă nu este liniștea totală, ci sunetele sintetice calibrate (AVAS), combinate cu sisteme de frânare automată. Totuși, factorul critic rămâne comportamentul pietonului (Jaywalking-ul), care, indiferent de tehnologia mașinii, rămâne principala cauză a incidentelor în modelul meu.

Vă mulțumesc!"

Tips pentru "Extra Points":
Dacă te întreabă de cod: Menționează clasa VehicleType – este un exemplu bun de Data-Driven Design (nu ai pus if uri peste tot, ci ai definit comportamentul în date).

Despre Traffic Light: Subliniază că ai implementat logica de semafor și coada de mașini ("Queueing logic"). Faptul că mașinile nu intră una în alta la semafor este o simulare fizică simplă, dar de efect.

Despre Jaywalkers: Explică faptul că "nerăbdarea" lor crește liniar în timp (self.impatience += 0.1), ceea ce face simularea dinamică, nu statică.
