#include <iostream>
#include <time.h>

#include "Interpreter.h"

int main()
{
    // (a + b * c) * d -> (10 + 5 * 2) * 6 = 120
    Context* context = new Context();
    context->SetVariable("a", 10);
    context->SetVariable("b", 5);
    context->SetVariable("c", 2);
    context->SetVariable("d", 6);

    IExpression* expression = new MultOperation(
        new AddOperation(new NumberExpression("a"),
            new MultOperation(new NumberExpression("b"),
                              new NumberExpression("c"))),
        new NumberExpression("d"));
    std::cout << expression->Interpret(context);
}


