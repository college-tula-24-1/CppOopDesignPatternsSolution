#include "Examples.h"

void DelegationPatternExample()
{
    UniversalVending vending;

    vending.Payment();
    vending.Select();
    vending.Receipt();

    vending.ToCigarette();

    vending.Payment();
    vending.Select();
    vending.Receipt();
}

void ImmutableInterfacePatternExample()
{
    Point2D* point = new Point2D();
    point->SetX(5);
    point->SetY(-7);

    IImmutablePoint2D* immutablePoint = new Point2D(5, 9);
    ((Point2D*)immutablePoint)->SetX(-5);
}
