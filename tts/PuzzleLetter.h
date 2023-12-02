#pragma once

using namespace System;
using namespace System::Windows::Forms;

public ref class PuzzleLetter : public Button {
public:
    property bool IsHighlighted;

    PuzzleLetter() {
        IsHighlighted = false;
    }
};
