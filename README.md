aircraft-assignment
===================

Automatic assignment of passengers to an aircraft

concepts: seats, passengers, aircraft

"assign" can mean

* booking, interactive
  - using a C++ class
  - Boost::uBlas for a 2d bool matrix (seat occupied/free)
  - C++ class exposed via Boost::Python
  - a Python program imports the shared library, and uses it in a Read-Eval-Print-Loop

* automatic placement
  - Python producing a webGL interactive scene. javascript functions from http://stemkoski.github.com
  - a complete solution would need to address different ticket types, 2d weight balance, groups of passengers booking together
    - multi-objective optimization, set packing, knapsack problem, ...
  - heuristics: groups of passengers and groups of seats are ranked, and processed so to achieve balance
