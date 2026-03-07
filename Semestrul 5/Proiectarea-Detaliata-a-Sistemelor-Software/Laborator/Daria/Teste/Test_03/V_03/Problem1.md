# Problem 1: Template Method vs Strategy

## 1. Comparație și Diferențe

### Inheritance (Static) vs Composition (Dynamic)

**Template Method** folosește **Inheritance (Moștenirea)**.
- Este considerată **statică** deoarece comportamentul este definit la momentul compilării prin structura de clase.
- Nu poți schimba algoritmul la runtime (decât dacă creezi o nouă instanță a altei subclase, ceea ce e greoi).
- Legătura dintre clasa de bază și subclase este foarte puternică.

**Strategy Pattern** folosește **Composition (Compoziția)**.
- Este considerată **dinamică** deoarece poți schimba obiectul `strategy` din interiorul Contextului oricând la runtime (`setStrategy()`).
- Contextul și Strategia sunt decuplate; Contextul știe doar de o interfață.

### Exemplu Concret (Diferit de Lab)

**Sistem de Sortare și Procesare a Datelor:**

1.  **Template Method (Static):**
    Avem o clasă abstractă `DataProcessor`.
    - Metoda `process()` (template) definește pașii: `readData()`, `sort()`, `saveData()`.
    - `sort()` este abstractă.
    - Avem subclase: `BubbleSortProcessor` și `QuickSortProcessor`.
    - **Limitarea:** Dacă am instanțiat un `BubbleSortProcessor`, acesta va folosi BubbleSort pentru totdeauna. Nu putem trece la QuickSort dacă datele devin prea mari în timpul execuției.

2.  **Strategy Pattern (Dynamic):**
    Avem clasa `DataProcessor` (Context) care are un câmp `SortingStrategy`.
    - Interfața `SortingStrategy` cu metoda `sort()`.
    - Implementări concrete: `BubbleSortStrategy`, `QuickSortStrategy`.
    - **Avantajul:** `DataProcessor` poate începe cu `BubbleSortStrategy`. Dacă detectează că a citit 1 milion de înregistrări, poate apela `setStrategy(new QuickSortStrategy())` la runtime, adaptându-se dinamic.

### Care este mai bun pentru "Reusable Code"?

**Strategy Pattern** este general considerat mai bun pentru cod reutilizabil și flexibil.
- Favorizează "Composition over Inheritance".
- Algoritmii (Strategiile) sunt clase separate, ușor de testat și reutilizat în alte contexte, nu sunt "blocați" în ierarhia procesorului.
- Respectă mai bine Open/Closed Principle: poți adăuga noi strategii fără a atinge clasa `DataProcessor`.

Template Method este util pentru framework-uri simple unde vrei să forțezi o structură rigidă a algoritmului, dar devine limitativ pe măsură ce sistemul crește.
