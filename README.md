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
