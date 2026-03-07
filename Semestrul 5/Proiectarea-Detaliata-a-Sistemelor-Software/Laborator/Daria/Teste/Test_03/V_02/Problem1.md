# Problem 1: Decorator vs Composite

## 1. Descriere și Exemple Concrete

### Decorator Pattern

**Descriere:**
Decorator este un tipar structural care permite adăugarea dinamică de funcționalități noi unui obiect existent, fără a modifica structura sa. Acesta folosește compoziția în loc de moștenire pentru a extinde comportamentul.

**Când este util:**
- Când vrei să adaugi responsabilități obiectelor în mod dinamic și transparent (fără ca codul client să știe).
- Când extinderea prin moștenire este nepractică (explozie de subclase pentru toate combinațiile posibile).

**Exemplu Concret (diferit de clasicele Coffee/Pizza):**
**Sistem de Notificări:**
Avem o componentă de bază `Notifier` care trimite emailuri. Vrem să putem trimite notificări și prin SMS, Facebook, sau Slack, în orice combinație.
- Component: `Notifier` (interface)
- ConcreteComponent: `EmailNotifier`
- Decorator: `BaseDecorator` (wraps Notifier)
- ConcreteDecorators: `SMSDecorator`, `FacebookDecorator`, `SlackDecorator`
Putem construi: `new SlackDecorator(new SMSDecorator(new EmailNotifier()))`.

### Composite Pattern

**Descriere:**
Composite este un tipar structural care îți permite să compui obiecte în structuri de tip arbore pentru a reprezenta ierarhii parte-întreg. Composite permite clienților să trateze obiectele individuale și compozițiile de obiecte în mod uniform.

**Când este util:**
- Când trebuie să implementezi o structură ierarhică de obiecte (arbore).
- Când vrei ca codul client să ignore diferența dintre obiecte simple și complexe (containere).

**Exemplu Concret (diferit de Files/Folders):**
**Menium unui Restaurant:**
Un meniu poate conține `Dish` (produs individual) sau `MenuCategory` (care conține alte `Dish`-uri sau `MenuCategory`-uri - ex: "Mic Dejun", "Deserturi").
- Component: `MenuComponent` (print(), getPrice())
- Leaf: `Dish` (ex: "Omletă", "Limonadă")
- Composite: `MenuCategory` (conține o listă de `MenuComponent`)
Întregul meniu este tratat uniform: poți apela `print()` pe tot meniul sau doar pe o categorie.

## 2. Principala Diferență

**Structura vs Scop:**
- **Decorator:** Scopul principal este **adăugarea de responsabilități** (funcționalitate) unui singur obiect. Relația este de obicei 1-la-1 (un decorator "învelește" un singur component).
- **Composite:** Scopul principal este **reprezentarea structurii** (ierarhie). Relația este de 1-la-mulți (un composite conține o colecție de copii).

Deși ambele folosesc compoziția recursivă (un obiect conține un obiect de același tip de bază), **Decoratorul** îmbogățește comportamentul, în timp ce **Composite-ul** agregă rezultatele copiilor (ex: calculează prețul total al sub-ramurii).
