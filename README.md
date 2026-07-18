# Restaurant Management System (C++)

A console-based Restaurant Management System built in C++ to apply core Object-Oriented Programming principles in a realistic, POS-style application — not just a toy example.

## Features

- **Menu Management** — add, modify, remove, and categorize items (Vegetarian, Vegan, Gluten-Free, Drinks)
- **Customer Registration** — tracks contact info and dietary preferences
- **Order Placement** — live bill calculation as items are ordered
- **Loyalty Points** — customers earn points per order and can redeem them at checkout
- **Persistent Storage** — file I/O keeps menu and customer data intact across sessions
- **Sales Tracking** — per-item sales logged for basic reporting

## OOP Concepts Applied

- **Abstraction & Polymorphism** — an abstract `CategoryBase` class overridden by `Vegetarian`, `Vegan`, `GlutenFree`, and `Drinks` subclasses
- **Encapsulation** — private fields with controlled access via getters and setters in `Menuitems` and `Customer`
- **Single-Responsibility Classes** — `MenuManager`, `CustomerRegistration`, and `OrderTaking` each handle one clear concern, keeping the codebase modular and easy to extend

## How It Works

The program runs as a menu-driven console application with three main modules:

1. **Modify Menu** — add, view, update, or remove menu items; view total sales per item
2. **Customer Registration** — register new customers, view customer details, or remove a customer
3. **Place an Order** — select a customer, browse the menu, add items to an order, and generate a final bill (with optional loyalty point redemption)

All menu and customer data is saved to `menu.txt` and `customers.txt`, so information persists between program runs.

## Tech Stack

C++ | File I/O | Object-Oriented Design

## Files

- `OOP PROJECT.cpp` — main source code
- `menu.txt` — persisted menu data
- `customers.txt` — persisted customer data

## Highlights / What I Learned

The most challenging part was the billing and loyalty points logic — handling partial point redemptions, preventing duplicate customer or menu entries, and keeping the customer file properly synced on every update or delete.

## Feedback

This was built as a learning project to strengthen OOP fundamentals. Feedback and suggestions are welcome!
