# 🚇 Metro Network Management System

A simple C-based console program to simulate and manage a metro rail network. This system allows users to input stations, lines, and connections (edges), and then perform various operations like finding routes, viewing station details, identifying intersections, and locating nearest intersections.

---

## 📁 Features

- Add edges with cost between metro stations
- Add metro lines and assign stations to lines
- Display:
  - All possible routes between two stations (with cost)
  - Information about a particular station
  - Intersections (stations with multiple lines)
  - Terminal stations of each line
  - Nearest intersection from a given station using BFS

---

## 🛠️ How It Works

- **Edge:** Connection between two stations with a cost.
- **Station:** Belongs to one or more lines.
- **Line:** A named group of stations in order.
- **DFS:** Used to find all possible routes between two stations.
- **BFS:** Used to find the nearest intersection from a given station.

---

## ▶️ How to Compile and Run

```bash
gcc metro.c -o metro
./metro
```

---

## 📌 Menu Options

1. **Find routes** – Enter source and destination to see all possible paths and their costs  
2. **Display station info** – See the lines and adjacent stations of a station  
3. **Display intersections** – Show stations that belong to multiple lines  
4. **Display terminal stations** – Show the first and last stations of each line  
5. **Find nearest intersection** – Find the nearest multi-line station from a given station  
6. **Exit** – Close the program  

---

## 📋 Sample Input Format

When prompted:

- **Edges:**
  ```
  Enter the number of edges: 3
  Enter source, destination, and cost:
  A B 5
  B C 4
  A C 7
  ```

- **Lines:**
  ```
  Enter the number of lines: 2
  Enter line name: Red
  Enter the number of stations in Red: 2
  Enter station name: A
  Enter station name: B
  Enter line name: Green
  Enter the number of stations in Green: 2
  Enter station name: B
  Enter station name: C
  ```

---

## 💡 Example Use Case

> **Query:** Find all routes from A to C  
> **Output:**  
> A -> B -> C, Cost: 9  
> A -> C, Cost: 7  

> **Query:** Display station info for B  
> **Output:**  
> Station Name: B  
> Lines: Red Green  
> Adjacent Stations: A (Cost: 5), C (Cost: 4)

---

## 🧠 Concepts Used

- Structures
- DFS & BFS
- Dynamic input mapping
- String manipulation
- Graph traversal logic

---

## 📞 Contact

Feel free to reach out if you have queries or need help with enhancements.
sumangujjarrao@gmail.com