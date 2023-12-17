#include <iostream>
#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

string Input::GetString(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}


double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{
	pO->PrintMessage("Please enter a value: ");
	string ReadInput = Input::GetString(pO); //read the input from the user
	while (!IsValue(ReadInput)) {	//Validation for the input
        pO->ClearStatusBar();
		pO->PrintMessage("Wrong input! Please enter valid value: ");
		ReadInput = Input::GetString(pO);
	}

	double D = std::stof(ReadInput); //change the string into double
	return D;
}


ActionType Input::GetUserAction() const {
    int x, y;
    pWind->WaitMouseClick(x, y); // Get the coordinates of the user click

    if (UI.AppMode == DESIGN) // application is in design mode
    {
        // Check if the user clicked on the toolbar
        if (y >= 0 && y < UI.ToolBarHeight) {
            int ClickedItem = (x / UI.MenuItemWidth);
            switch (ClickedItem) {
            case ITM_START: return ADD_START;
            case ITM_END: return ADD_END;
            case ITM_VALUE_ASSIGN: return ADD_VALUE_ASSIGN;
            case ITM_VAR_ASSIGN: return ADD_VAR_ASSIGN;
            case ITM_OPER_ASSIGN: return ADD_OPER_ASSIGN;
            case ITM_COND: return ADD_CONDITION;
            case ITM_READ: return ADD_READ;
            case ITM_WRITE: return ADD_WRITE;
            case ITM_CONNECTOR: return ADD_CONNECTOR;
            case ITM_SELECT: return SELECT;
            case ITM_EDIT_STAT: return EDIT_STAT;
            case ITM_DEL: return DEL;
            case ITM_COPY: return COPY;
            case ITM_CUT: return CUT;
            case ITM_PASTE: return PASTE;
            case ITM_SAVE: return SAVE;
            case ITM_LOAD: return LOAD;
            case ITM_SWITCH_SM: return SWITCH_SIM_MODE;
            case ITM_EXIT: return EXIT;
                // Add cases for other design menu items
            default: return DSN_TOOL;
            }
        }

        // Check if the user clicked on the drawing area
        else if (y >= UI.ToolBarHeight && y < (UI.height - UI.StatusBarHeight)) {
            if (x <= UI.DrawingAreaWidth) {
                return DRAWING_AREA;
            }
            else {
                return OUTPUT_AREA;
            }
        }

        // Check if the user clicked on the status bar
        return STATUS;
    }
    else // Application is in Simulation mode
    {
        // Check if the user clicked on the toolbar
        if (y >= 0 && y < UI.ToolBarHeight) {
            int ClickedItem = (x / UI.MenuItemWidth);
            switch (ClickedItem) {
            case ITM_VALIDATE: return VALIDATE;
            case ITM_RUN: return RUN;
            case ITM_SWITCH_DS: return SWITCH_DSN_MODE;
            case ITM_EXIT1: return EXIT;  // Exit simulation mode
                // Add cases for other simulation menu items
            default: return SIM_TOOL;
            }
        }

        // Check if the user clicked on the drawing area in simulation mode
        else if (y >= UI.ToolBarHeight && y < (UI.height - UI.StatusBarHeight)) {
            if (x <= UI.DrawingAreaWidth) {
                return DRAWING_AREA;
            }
            else {
                return OUTPUT_AREA; // It's still possible to click the output area in simulation mode
            }
        }

        // Check if the user clicked on the status bar in simulation mode
        return STATUS;
    }
}


string Input::GetVariable(Output* pO) const
{
	pO->PrintMessage("Please enter a variable: ");
	string ReadInput = Input::GetString(pO); //read the input from the user
	while (!IsVariable(ReadInput)) {	//Validation for the input
    pO->ClearStatusBar();
	pO->PrintMessage("Wrong input! Please enter a valid variable: ");
		ReadInput = Input::GetString(pO);
	}
	return ReadInput; 
}
string Input::GetArithOperator(Output* pO)const {
    string ReadInput = Input::GetString(pO);
    while (ReadInput.length() > 1 || !(ReadInput == "+" || ReadInput == "-" || ReadInput == "*" || ReadInput == "/"))//Won't exit until user inputs the correct input
    {
            pO->PrintMessage("Invalid operator,please enter a valid operator: ");//display error and ask for input again
            ReadInput = Input::GetString(pO);
    }
        return ReadInput;
}
string Input::GetCompOperator(Output* pO) const {
    string ReadInput = Input::GetString(pO);
    /*std::cout << "Enter a comparison operator Ex.(==, !=, <, <=, >, or >=): ";*/
    while (ReadInput.length() > 2 || !(ReadInput == "==" || ReadInput == "!=" 
        || ReadInput == ">" || ReadInput == "<" || ReadInput == "<=" || ReadInput == ">=")) { // Won't exit until the user inputs the correct input
        pO->PrintMessage("Invalid operator,please enter a valid operator: ");//display error and ask for input again
        ReadInput = Input::GetString(pO);
    }
    return ReadInput;
}

Input::~Input()
{
}
