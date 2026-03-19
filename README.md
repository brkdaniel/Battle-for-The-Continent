# Battle for The Continent (C++ Card Game Engine

A text-based card game inspired from Gwent, The Witcher 3 card-game. I built the engine from scratch using modern C++
This project is like a playground where I applied core Object-Oriented Programming (OOP) concepts, memory safety rules, and automated testing.

## ⚙️ Technical Features

I focused on writing clean, scalable, and crash-free code. Here is how the engine is built:

* **No Manual Memory Management:** I used Smart Pointers (`std::unique_ptr`) exclusively for managing the deck and the cards on the board. This guarantees zero memory leaks and eliminates the need for manual `delete` calls.
* **Design Patterns:**
  * **Factory Pattern (`CardFactory`):** Instead of hardcoding card creation, the Factory dynamically generates the right type of card (Unit, Weather, Special) based on input data (like a text file).
  * **Singleton (`GameApp`):** Ensures there is only one central game engine running the main loop.
* **Templates & Generic Programming:** The `Deck` class uses template methods (e.g., `getCardsOfType<T>()`) to easily filter and find specific card types without writing duplicate code.
* **STL Algorithms:** Replaced traditional `for` loops with modern C++ algorithms like `std::accumulate` (for calculating row power) and `std::sort` with lambda expressions.
* **Polymorphism:** A solid base `Card` class allows derived cards to have their own specific rules (e.g., a `WeatherCard` acts differently than a `UnitCard`).



## ⚙️ DevOps & Code Quality

It works on my machine, but I wanted to make sure it works everywhere. The repository includes an automated CI/CD pipeline:
* **GitHub Actions:** Automatically compiles and tests the project on every push.
* **Memory Safety:** The pipeline runs **Valgrind**, **AddressSanitizer (ASan)**, and **MemorySanitizer (MSan)** to prove the code is free of leaks and undefined behavior.
* **Static Analysis:** Integrated **Cppcheck** to enforce strict C++ coding styles and catch performance warnings.

## 🗺️ What's Next

This project is still in the works. While the core engine and memory management are stable, here is what I am planning to implement next:

* **[In Progress]** Advanced game loop with complete turn-based mechanics and win/loss conditions.
* **[Planned]** Implementation of more Design Patterns (e.g., Observer for event handling when cards are played).
* **[Planned]** Expanded deck varieties and custom card abilities.
* **[Future]** A potential migration from text-based CLI to a graphical interface (GUI).