#include "../Robot.h"

#include "VenomShot.h"

VenomShot::VenomShot()
{
    //ctor
}

VenomShot::VenomShot(Robot *parent)
{
    this->shottype = -3;
    this->color.set(1, 0, 0);

    this->value = min((__int16)parent->Venom, (*parent)[shootval]);
    parent->Venom -= this->value;
}

VenomShot::~VenomShot()
{
    //dtor
}

const float VenomShot::hit(Robot* target) const
{
    return 0.;
}

const bool VenomShot::bouncesOff(const Robot *const target, const float &power) const
{
    return false;
}

Shot* VenomShot::returnShot(const Robot* target, const float &power) const
{
    throw;
}

/*void VenomShot::collide(Robot *target)
{
    Dim power As Long

  power = Shots(t).nrg / (Shots(t).range * (RobSize / 3)) * Shots(t).value

  If Shots(t).Memloc = 340 Or power < 1 Then Exit Sub 'protection from delgene attacks

  If Shots(t).FromSpecie = rob(n).fname Then   'Robot is imune to venom from his own species
    rob(n).venom = rob(n).venom + power   'Robot absorbs venom fired by conspec
    rob(n).mem(825) = rob(n).venom
  Else
    If power < rob(n).Shell * ShellEffectiveness Then
      rob(n).Shell = rob(n).Shell - power / ShellEffectiveness
    Else
      Dim temp As Long
      temp = power
      power = power - rob(n).Shell * ShellEffectiveness
      rob(n).Shell = rob(n).Shell - temp / ShellEffectiveness
      If rob(n).Shell < 0 Then rob(n).Shell = 0
    End If

    If power < 0 Then Exit Sub

    rob(n).Paralyzed = True
    rob(n).Paracount = rob(n).Paracount + power

    If Shots(t).Memloc > 0 Then
      If Shots(t).Memloc > 1000 Then Shots(t).Memloc = (Shots(t).Memloc - 1) Mod 1000 + 1
      rob(n).Vloc = Shots(t).Memloc
    Else
      rob(n).Vloc = fRnd(1, 1000)
    End If

    rob(n).Vval = Shots(t).Memval
  End If
  Shots(t).Exist = False

}*/
