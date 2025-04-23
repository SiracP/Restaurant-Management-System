# Restaurant Management System

A Qt/C++ desktop application providing end-to-end management for a small restaurant. It features a responsive, modern UI built with Qt Widgets, backed by a singleton `Restaurant` core that tracks tables, orders, payments, and sales history. Interactive dashboards, real-time clock, and rich charts keep staff informed and streamline day-to-day operations.

## Key Features

- **Home Dashboard**  
  • Live clock and date display  
  • **Daily Sales** summary card showing total revenue  
  • **Active Tables** indicator (occupied vs. total)  
  • **Top Product** by revenue  
  • Scrollable **Recent Activities** log  
  • Decorative, responsive background photo  

- **Tables & Orders**  
  • Select any of N tables to view or edit current orders  
  • Add/remove items via intuitive “cards” with product images and ± buttons  
  • In-progress draft mode before committing changes  
  • Automatic table occupancy tracking  

- **Checkout & Payments**  
  • View a breakdown of ordered items with quantities, unit prices, and subtotals  
  • Partial payments: check off individual items or enter a custom amount  
  • Handles remaining balances and carries them over to the next session  
  • Records each sale for reporting and recent-activity logging  

- **Product Catalog**  
  • Scrollable grid of all menu items with images, names, and prices  
  • Easily extend or modify by editing the JSON menu resource

- **Reports & Analytics**  
  • **Pie chart** of revenue distribution by product  
  • **Bar chart** of units sold per product  
  • Tabular breakdown of total units per item  
  • Highlights top-selling products and overall performance  

## Architecture

- **Singleton Data Core (`Restaurant`)**  
  Centralizes all state and business logic: manages table objects, global product catalog, cumulative sales totals, per-product breakdowns, and a rolling “recent activities” log. Ensures a single, shared source of truth across the UI.

- **Modular Page Widgets**  
  By adopting a Single-Page Application (SPA) pattern, all screens (HomePage, TablesPage, OrderPage, CheckoutPage, ProductsPage, ReportsPage) are instantiated up front and hosted in a single QStackedWidget. Each page is a self-contained QWidget subclass that handles its own layout, data loading, and user interactions. Only one page is ever visible at a time—hidden pages retain their state—enabling seamless, high-performance navigation without recreating windows. This modular SPA approach preserves clear separation of concerns, simplifies event wiring, and makes the codebase both scalable and maintainable.

- **Resource-Driven Catalog & Localization**  
  Products are loaded from a JSON resource (`:/data/menu.json`) with image assets under `:/images/`. The `ProductCatalog` parses and caches these entries, allowing the UI to dynamically reflect menu changes without recompilation.

- **Responsive Layouts & Ownership**  
  Utilizes Qt’s layout managers (`QVBoxLayout`, `QHBoxLayout`, `QGridLayout`) with expanding size policies for fluid resizing. Parent–child widget ownership and smart pointers in the catalog prevent memory leaks and simplify cleanup.

*Built with Qt 6, C++17, and QtCharts. Designed for small-to-medium restaurants seeking a lightweight, offline management tool.*

- **Screenshots**
  
*Tables Page*
![Tablespage](https://github.com/user-attachments/assets/aea15103-7fdd-4c68-b558-510d08f70014)

*Add Order Page*
![AddOrderPage](https://github.com/user-attachments/assets/e5686df0-392a-4c7e-aed3-b327632c6cf8)

*CheckoutPage*
![CheckoutPage1](https://github.com/user-attachments/assets/111e4bf9-ba97-41fd-b087-d68662c88398)
![CheckoutPage2](https://github.com/user-attachments/assets/0796b399-58dc-469f-98b3-3ea5ed773ecf)

*Products Page*
![ProductsPage](https://github.com/user-attachments/assets/355c44ef-e695-4fdf-b68a-a9c75e6eceda)

*Reports Page*
![ReportsPage1](https://github.com/user-attachments/assets/f131ae99-20b9-4f45-b76b-0dbc37fc157f)
![ReportsPage2](https://github.com/user-attachments/assets/e0f474bc-18a2-4325-9ed5-82985c28f46c)

*Home Page*
![HomePage](https://github.com/user-attachments/assets/8112c746-a8d1-409e-87ad-d064c3c3aa33)
![HomePageFull](https://github.com/user-attachments/assets/7641e635-f8c4-48d9-952d-896869c7c190)
