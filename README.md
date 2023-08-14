# Sorting Yu-Gi-Oh! Trading Cards

In this project, we will work with several classes to implement sorting algorithms for Yu-Gi-Oh! trading cards. The main classes involved are:

## YGOCard Class
The `YGOCard` class represents a Yu-Gi-Oh! trading card. It has 7 data members: 
- Name of the card
- Type of card
- Level (or rank) of the card
- Attribute of the card (Wind, Earth, Fire, Water)
- Race of the monster on the card (Machine, Dragon, Fiend)
- Attack points (atk) of the monster
- Defense points (def) of the monster

For this project, we focus on 3 elements: name, atk, and def. The cards will be sorted based on attack value.

## DoublyLinkedList and Node Classes
We utilize the `DoublyLinkedList` class and the associated `Node` class to implement a doubly-linked list data structure.

## CardShop Class
The `CardShop` class inherits from `DoublyLinkedList` and is used to manage the trading card shop. Its parameterized constructor reads from an input file and populates the shop with pointers to corresponding `YGOCard` objects (pointers to `YGOCard` objects, not the objects themselves). The `CardShop` class extends `DoublyLinkedList` by implementing 4 sorting algorithms to sort `YGOCard` objects by metrics such as attack (atk) and defense (def).

## Data Source
The card data is stored in a CSV file, which is our Yu-Gi-Oh! cards dataset. This dataset has been pre-processed to remove special characters that could conflict with Gradescope. Please use the provided `cards.csv` file in the starter files.

## Acknowledgments
The dataset used for this project is sourced from Kaggle.

## Getting Started
- Clone this repository.
- Review linked lists and sorting algorithms to understand the project requirements.
- Use the provided starter files.
- Implement the sorting algorithms in the `CardShop` class to sort the `YGOCard` objects.

## Note
Starter files for this project will be provided. If you encounter difficulties with linked lists and sorting algorithms, consider seeking tutoring assistance in the lab.

Good luck and have fun sorting those Yu-Gi-Oh! trading cards!
