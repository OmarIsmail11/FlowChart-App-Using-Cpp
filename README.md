# FLowChart windows application Using c++

## Overview
This Windows Flow Chart Application is a user-friendly tool for designing, editing, and managing flow charts. It allows users to visually map out processes, workflows, or algorithms with ease providing an intuitive interface for creating professional flow charts. Designed for simplicity and efficiency, this application helps streamline complex workflows into clear, structured visualizations. Whether you're planning software architectures, business processes, or educational diagrams, this tool provides an intuitive interface for creating professional flow charts. 
## Features
- Modern Easy to Use GUI
- Drag-and-Drop Interface
- Smooth Connectors
- Auto-Align and Snap
- Undo/Redo Functionality
- Copy/Paste Shapes
- Project Save/Load
- Auto FlowChart Validation
## Project Structure

```C++
/flowchart-app
|-- src
|   |-- main.cpp
|   |-- ApplicationManager.cpp
|-- include
|   |-- ApplicationManager.h
|-- Statements
|   |-- Statement.cpp
|   |-- Start.cpp
|   |-- End.cpp
|   |-- OpAssign.cpp
|   |-- Read.cpp
|   |-- ValueAssign.cpp
|   |-- VarAssign.cpp
|   |-- Write.cpp
|-- include
|   |-- Statement.h
|   |-- Start.h
|   |-- End.h
|   |-- OpAssign.h
|   |-- Read.h
|   |-- ValueAssign.h
|   |-- VarAssign.h
|   |-- Write.h
|--Actions
|   |-- Action.cpp
---include
|   |-- Action.h
|-- diagrams
|   |-- ClassDiagram.cd
```
