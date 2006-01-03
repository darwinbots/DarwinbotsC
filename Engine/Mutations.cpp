#include "DNAClass.h"

struct MutationsType
{
    long PointPerUnit;  //per x cycles
    long PointCycle;    //the cycle we are going to point mutate during
    float PointMean;    //average length of DNA to change
    float PointStdDev;  //std dev of this length

    long ReproduceTotalPerUnit;     //
    long Reproduce;                 //a 1 in X change to mutate when we reproduce

    long ReversalPerUnit;           //
    float ReversalLengthMean;       //
    float ReversalLengthStdDev;     //

    long CopyErrorPerUnit;          //
    long InsertionPerUnit;
    long AmplificationPerUnit;
    long MajorDeletionPerUnit;
    long MinorDeletionPerUnit;
};

//1-(perbot+1)^(1/DNALength) = per unit
//1-(1-perunit)^DNALength = perbot

enum MUTATIONS_UP
{
    PointUP = 0,
    MinorDeletionUP,
    ReversalUP,
    InsertionUP,
    AmplificationUP,
    MajorDeletionUP,
    CopyErrorUP,
    DeltaUP,
    TranslocationUP
};

string &MutationType(MUTATIONS_UP mode)
{
    static string temp("");

    switch(mode)
    {
        case PointUP:
            temp = "Point Mutation";
            break;
        case MinorDeletionUP:
            temp = "Minor Deletion";
            break;
        case ReversalUP:
            temp = "Reversal";
            break;
        case InsertionUP:
            temp = "Insertion";
            break;
        case AmplificationUP:
            temp = "Amplification";
            break;
        case MajorDeletionUP:
            temp = "Major Deletion";
            break;
        case CopyErrorUP:
            temp = "Copy Error";
            break;
        case DeltaUP:
            temp = "Delta Mutation";
            break;
        case TranslocationUP:
            temp = "Translocation";
            break;
    }
    
    return temp;
}

//NEVER allow anything after end, which must be = DNALen
//ALWAYS assume that DNA is sized right
//ALWAYS size DNA correctly when mutating

/*Public Function MakeSpace(ByRef DNA() As block, ByVal beginning As Long, ByVal length As Long, Optional DNALength As Integer = -1) As Boolean
  'add length elements after beginning.  Beginning doesn't move places
  'returns true if the space was created,
  'false otherwise

  Dim t As Integer
  If DNALength < 0 Then DNALength = DnaLen(DNA)
  If length < 1 Or beginning < 0 Or beginning > DNALength - 1 Then
    MakeSpace = False
    Exit Function
  End If
  
  MakeSpace = True

  ReDim Preserve DNA(DNALength + length)

  For t = DNALength To beginning + 1 Step -1
    DNA(t + length) = DNA(t)
    EraseUnit DNA(t)
  Next t
End Function

Public Sub Delete(ByRef DNA() As block, ByRef beginning As Long, ByRef elements As Long, Optional DNALength As Integer = -1)
  'delete elements starting at beginning
  Dim t As Integer
  If DNALength < 0 Then DNALength = DnaLen(DNA)
  If elements < 1 Or beginning < 1 Or beginning > DNALength - 1 Then Exit Sub
  If elements + beginning > DNALength - 1 Then elements = DNALength - 1 - beginning

  For t = beginning + elements To DNALength
    DNA(t - elements) = DNA(t)
  Next t

  DNALength = DnaLen(DNA)
  ReDim Preserve DNA(DNALength)
End Sub
*/

//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''

bool DNA_Class::Mutate(bool reproducing = false) //returns wether we should mutate colors or not
{
    long delta;

    delta = this->LastMut;

    if (this->Mutables.Mutations == false)
        return false;

    if (!reproducing)
    {
        //if (this->Mutables.mutarray[PointUP] > 0) this->PointMutation();
        //if (this->Mutables.mutarray[DelatUP] > 0) this->DeltaMut();
    }
    else
    {
        //if (this->Mutables.mutarray[CopyErrorUP] > 0) this->CopyError();
        //if (this->Mutables.mutarray[InsertionUP] > 0) this->Insertion();
        //if (this->Mutables.mutarray[ReversalUP] > 0) this->Reversal();
        //if (this->Mutables.mutarray[TranslocationUP] > 0) this->Translocation();
        //if (this->Mutables.mutarray[AmplificationUP] > 0) this->Amplification();
        //if (this->Mutables.mutarray[MajorDeletionUP] > 0) this->MajorDeletion();
        //if (this->Mutables.mutarray[MinorDeletionUP] > 0) this->MinorDeletion();
    }

    delta = this->LastMut - delta;

    if (delta > 0)
        return true; //mutate colors
        
    return false;
}


/*
Private Sub PointMutation(ByVal robn As Long)
  'assume the bot has a positive (>0) mutarray value for this
  With rob(robn)
    If .age = 0 Or .PointMutCycle < .age Then PointMutWhereAndWhen Rnd, robn, .PointMutBP

    'in case we get two point mutations in a single cycle, this must be a while
    While .age = .PointMutCycle
      ChangeDNA robn, .PointMutBP, Gauss(.Mutables.StdDev(PointUP), .Mutables.Mean(PointUP)), .Mutables.PointWhatToChange
      PointMutWhereAndWhen Rnd, robn, .PointMutBP
    Wend
  End With
End Sub

Private Sub PointMutWhereAndWhen(randval As Single, robn As Long, Optional offset As Long = 0)
  Dim result As Single
  
  'If randval = 0 Then randval = 0.0001
  With rob(robn)
  If .Mutables.mutarray(PointUP) > 0 Then
    'result = offset + Fix(Log(randval) / Log(1 - 1 / (1000 * .Mutables.mutarray(PointUP))))
    result = Log(1 - randval) / Log(1 - 1 / (1000 * .Mutables.mutarray(PointUP)))
    .PointMutBP = (result Mod (.DnaLen - 1)) + 1 'note that DNA(DNALen) = end.
      'We don't mutate end.  Also note that DNA does NOT start at 0th element
    .PointMutCycle = .age + result / (.DnaLen - 1)
  End If
  End With
End Sub

Private Sub DeltaMut(robn As Integer)
  Dim temp As Integer
  Dim newval As Long
    
  With rob(robn)

  If Rnd > 1 - 1 / (100 * .Mutables.mutarray(DeltaUP)) Then
    If .Mutables.StdDev(DeltaUP) = 0 Then .Mutables.Mean(DeltaUP) = 50
    If .Mutables.Mean(DeltaUP) = 0 Then .Mutables.Mean(DeltaUP) = 25
    
    'temp = fRnd(0, 20)
    Do
      temp = fRnd(0, 7)
    Loop While .Mutables.mutarray(temp) <= 0
    
    Do
      newval = Gauss(.Mutables.Mean(DeltaUP), .Mutables.mutarray(temp))
    Loop While .Mutables.mutarray(temp) = newval Or newval <= 0
    
    .LastMutDetail = "Delta mutations changed " + MutationType(temp) + " from 1 in" + Str(.Mutables.mutarray(temp)) + _
      " to 1 in" + Str(newval) + vbCrLf + .LastMutDetail
    .Mutations = .Mutations + 1
    .LastMut = .LastMut + 1
    .Mutables.mutarray(temp) = newval
  End If
  
  End With
End Sub

Private Sub CopyError(robn As Integer)
  Dim t As Long
  Dim accum As Long
  Dim length As Long
  
  With rob(robn)
  
  For t = 1 To (.DnaLen - 1) 'note that DNA(.dnalen) = end, and we DON'T mutate that.
   
    If Rnd < 1 / rob(robn).Mutables.mutarray(CopyErrorUP) Then
      length = Gauss(rob(robn).Mutables.StdDev(CopyErrorUP), _
        rob(robn).Mutables.Mean(CopyErrorUP)) 'length
      accum = accum + length
      ChangeDNA robn, t, length, rob(robn).Mutables.CopyErrorWhatToChange, _
        CopyErrorUP
    End If
  Next t
  
  End With
End Sub

'Private Sub ChangeDNA(ByRef DNA() As block, nth As Long, Optional length As Long = 1)
Private Sub ChangeDNA(ByVal robn As Integer, ByVal nth As Long, Optional ByVal length As Long = 1, Optional ByVal PointWhatToChange As Integer = 50, Optional Mtype As Integer = PointUP)
  'currently only mutates the value.  Later we may change it to accept changes
  'in type
  
  'we need to rework .lastmutdetail

  With rob(robn)

  Dim t As Long
  For t = nth To (nth + length - 1) 'if length is 1, it's only one bp we're mutating, remember?
    If t >= .DnaLen Then Exit Sub 'don't mutate end either
    If .DNA(t).tipo = 10 Then Exit Sub 'mutations can't cross control barriers
    Dim old As Long

    If fRnd(0, 99) < PointWhatToChange Then
      '''''''''''''''''''''''''''''''''''''''''
      'Mutate VALUE
      '''''''''''''''''''''''''''''''''''''''''
      If .DNA(t).value And Mtype = InsertionUP Then
        'Insertion mutations should get a good range for value.
        'Don't worry, this will get "mod"ed for non number commands.
        'This doesn't count as a mutation, since the whole:
        ' -- Add an element, set it's tipo and value to random stuff -- is a SINGLE mutation
        'we'll increment mutation counters and .lastmutdetail later.
        .DNA(t).value = Gauss(500, 0) 'generates values roughly between -1000 and 1000
      End If
      
      Dim Max As Long
      Dim temp As String
      Dim bp As block
      Dim Name As String
      Dim oldname As String
      
      old = .DNA(t).value
      
      If .DNA(t).tipo = 0 Or .DNA(t).tipo = 1 Then '(number or *number)
        Do
          Dim a As Integer
          .DNA(t).value = Gauss(IIf(Abs(old) < 100, IIf(Sgn(old) = 0, fRnd(0, 1) * 2 - 1, Sgn(old)) * 10, old / 10), .DNA(t).value)
        Loop While .DNA(t).value = old

        .Mutations = .Mutations + 1
        .LastMut = .LastMut + 1
        .LastMutDetail = MutationType(Mtype) + " changed " + TipoDetok(.DNA(t).tipo) + " from" + Str(old) + " to" + Str(.DNA(t).value) + " at position" + Str(t) + " during cycle" + Str(SimOpts.TotRunCycle) + vbCrLf + .LastMutDetail
      Else
        'find max legit value
        'this should really be done a better way
        bp.tipo = .DNA(t).tipo
        Max = 0
        Do
          temp = ""
          Max = Max + 1
          bp.value = Max
          Parse temp, bp
        Loop While temp <> ""
        Max = Max - 1
        If Max <= 1 Then Exit Sub 'failsafe in case its an invalid type or there's no way to mutate it
        
        Do
          .DNA(t).value = fRnd(1, Max)
        Loop While .DNA(t).value = old

        bp.tipo = .DNA(t).tipo
        bp.value = old

        Parse Name, .DNA(t)
        Parse oldname, bp

        .Mutations = .Mutations + 1
        .LastMut = .LastMut + 1
        .LastMutDetail = MutationType(Mtype) + " changed value of " + TipoDetok(.DNA(t).tipo) + " from " + _
          oldname + " to " + Name + " at position" + Str(t) + " during cycle" + _
          Str(SimOpts.TotRunCycle) + vbCrLf + .LastMutDetail
      End If
    Else
      
      bp.tipo = .DNA(t).tipo
      bp.value = .DNA(t).value
      
      Do
        .DNA(t).tipo = fRnd(0, 20)
      Loop While .DNA(t).tipo = bp.tipo Or TipoDetok(.DNA(t).tipo) = ""
      
      Max = 0
      If .DNA(t).tipo >= 2 Then
        Do
          temp = ""
          Max = Max + 1
          .DNA(t).value = Max
          Parse temp, .DNA(t)
        Loop While temp <> ""
        Max = Max - 1
        If Max <= 1 Then Exit Sub 'failsafe in case its an invalid type or there's no way to mutate it
        
        .DNA(t).value = (bp.value Mod Max) 'put values in range
        If .DNA(t).value <= 0 Then
          .DNA(t).value = 1
        End If
      Else
        'we do nothing, it has to be in range
      End If

      Parse Name, .DNA(t)
      Parse oldname, bp
      
      .Mutations = .Mutations + 1
      .LastMut = .LastMut + 1
      
      .LastMutDetail = MutationType(Mtype) + " changed the " + TipoDetok(bp.tipo) + ": " + _
          oldname + " to the " + TipoDetok(.DNA(t).tipo) + ": " + Name + " at position" + Str(t) + " during cycle" + _
          Str(SimOpts.TotRunCycle) + vbCrLf + .LastMutDetail
    End If
  Next t
  End With
End Sub

Private Sub Insertion(robn As Integer)
  Dim location As Integer
  Dim length As Integer
  Dim accum As Long
  Dim t As Long
  
  With rob(robn)
  For t = 1 To (.DnaLen - 1)
    If Rnd < 1 / .Mutables.mutarray(InsertionUP) Then
      If .Mutables.Mean(InsertionUP) = 0 Then .Mutables.Mean(InsertionUP) = 1
      Do
        length = Gauss(.Mutables.StdDev(InsertionUP), .Mutables.Mean(InsertionUP))
      Loop While length <= 0
      
      MakeSpace .DNA(), t + accum, length, .DnaLen
      rob(robn).DnaLen = rob(robn).DnaLen + length
      accum = accum + length
      ChangeDNA robn, t + accum, length, 100, InsertionUP 'set a good value up
      ChangeDNA robn, t + accum, length, 0, InsertionUP 'change type
    End If
  Next t
  End With
End Sub

Private Sub Reversal(robn As Integer)
  'reverses a length of DNA
  Dim length As Long
  Dim counter As Long
  Dim location As Long
  Dim low As Long
  Dim high As Long
  Dim templong As Long
  Dim tempblock As block
  Dim t As Long
  Dim second As Long
  
  With rob(robn)
    For t = 1 To (.DnaLen - 1)
      If Rnd < 1 / .Mutables.mutarray(ReversalUP) Then
        If .Mutables.Mean(ReversalUP) < 2 Then .Mutables.Mean(ReversalUP) = 2
        
        Do
          length = Gauss(.Mutables.StdDev(ReversalUP), .Mutables.Mean(ReversalUP))
        Loop While length <= 0
        
        length = length \ 2 'be sure we go an even amount to either side
        
        If t - length < 1 Then length = t - 1
        If t + length > .DnaLen - 1 Then length = .DnaLen - 1 - t
        If length > 0 Then
        
          second = 0
          For counter = t - length To t - 1
            tempblock = .DNA(counter)
            .DNA(counter) = .DNA(t + length - second)
            .DNA(t + length - second) = tempblock
            second = second + 1
          Next counter
          
          .Mutations = .Mutations + 1
          .LastMut = .LastMut + 1
          .LastMutDetail = "Reversal of" + Str(length * 2 + 1) + "bps centered at " + Str(t) + " during cycle" + _
            Str(SimOpts.TotRunCycle) + vbCrLf + .LastMutDetail
        End If
      End If
    Next t
  End With
End Sub

Private Sub MinorDeletion(robn As Integer)
  Dim length As Long, t As Long
  With rob(robn)
    If .Mutables.Mean(MinorDeletionUP) < 1 Then .Mutables.Mean(MinorDeletionUP) = 1
    For t = 1 To (.DnaLen - 1)
      If Rnd < 1 / .Mutables.mutarray(MinorDeletionUP) Then
        Do
          length = Gauss(.Mutables.StdDev(MinorDeletionUP), .Mutables.Mean(MinorDeletionUP))
        Loop While length <= 0
        
        If t + length > .DnaLen - 1 Then length = .DnaLen - 1 - t
        
        Delete .DNA, t, length, .DnaLen
        
        .DnaLen = DnaLen(.DNA())
        
        .LastMutDetail = "Minor Deletion deleted a run of" + _
          Str(length) + " bps at position" + Str(t) + " during cycle" + _
          Str(SimOpts.TotRunCycle) + vbCrLf + .LastMutDetail
      End If
    Next t
  End With
End Sub

Private Sub MajorDeletion(robn As Integer)
  Dim length As Long, t As Long
  With rob(robn)
    If .Mutables.Mean(MajorDeletionUP) < 1 Then .Mutables.Mean(MajorDeletionUP) = 1
    For t = 1 To (.DnaLen - 1)
      If Rnd < 1 / .Mutables.mutarray(MajorDeletionUP) Then
        Do
          length = Gauss(.Mutables.StdDev(MajorDeletionUP), .Mutables.Mean(MajorDeletionUP))
        Loop While length <= 0
        
        If t + length > .DnaLen - 1 Then length = .DnaLen - 1 - t
        
        Delete .DNA, t, length, .DnaLen
        
        .DnaLen = DnaLen(.DNA())
        
        .Mutations = .Mutations + 1
        .LastMut = .LastMut + 1
        .LastMutDetail = "Major Deletion deleted a run of" + _
          Str(length) + " bps at position" + Str(t) + " during cycle" + _
          Str(SimOpts.TotRunCycle) + vbCrLf + .LastMutDetail
      End If
    Next t
  End With
End Sub

Private Sub Amplification(robn As Integer)
  '1. pick a spot (1 to .dnalen - 1)
  '2. Run a length, copied to a temporary location
  '3.  Pick a new spot (1 to .dnalen - 1)
  '4. Insert copied DNA
  
  Dim t As Long
  Dim length As Long
  With rob(robn)
  Dim tempDNA() As block
  Dim start As Long
  Dim second As Long
  Dim counter As Long
  
  For t = 1 To .DnaLen - 1
    If Rnd < 1 / .Mutables.mutarray(AmplificationUP) Then
      length = Gauss(.Mutables.StdDev(AmplificationUP), .Mutables.Mean(AmplificationUP))
      If length < 1 Then length = 1
      
      length = length - 1
      length = length \ 2
      If t - length < 1 Then length = t - 1
      If t + length > .DnaLen - 1 Then length = .DnaLen - 1 - t
      
      If length > 0 Then
      
        ReDim tempDNA(length * 2 + 1)
      
        'add "end" to end of temporary DNA
        tempDNA(length * 2 + 1).tipo = 10
        tempDNA(length * 2 + 1).value = 1
        
        second = 0
        For counter = t - length To t + length
          tempDNA(second) = .DNA(counter)
          second = second + 1
        Next counter
        'we now have the appropriate length of DNA in the temporary array.
      
        'open up a hole
        start = fRnd(1, .DnaLen - 1)
        MakeSpace .DNA(), start, DnaLen(tempDNA), .DnaLen
           
        For counter = start + 1 To start + DnaLen(tempDNA)
          .DNA(counter) = tempDNA(counter - start - 1)
        Next counter
      
        'done!  weee!
        .Mutations = .Mutations + 1
        .LastMut = .LastMut + 1
        .LastMutDetail = "Amplification copied a series at" + Str(t) + Str(length * 2 + 1) + "bps long to " + Str(start) + " during cycle" + _
          Str(SimOpts.TotRunCycle) + vbCrLf + .LastMutDetail
      End If
    End If
  Next t
  End With
End Sub

Private Sub Translocation(robn As Integer)
  'Bug testing has not been comprehensive for this function
  'This could be a potential source for bugs
  
  'If this function looks like mish mash, the best way to figure it out is to walk through
  'in debug mode.  Then it makes much more sense.  If you don't have a firm grasp of the debug
  'controls, I'd recommend spending the time to figure them out.  Well worth it.
  
  '1. Find a spot (spot = x) (range: 1 to dnalen - 1)
  '2. cut out from the rest of the DNA a segment length long centered at x
  '3. Close gap in DNA
  '4. Find new spot in DNA (spot = y) (range: 0, dnalen - 1)
  '5. Starting at y, add segment after it.
  
  Dim t As Long, counter As Long
  Dim length As Long
  Dim tempDNA() As block
  Dim second As Long
  Dim start As Long
  
  With rob(robn)
  
  If .Mutables.Mean(TranslocationUP) < 1 Then .Mutables.Mean(TranslocationUP) = 1
  For t = 1 To .DnaLen - 1
    If Rnd < 1 / .Mutables.mutarray(TranslocationUP) Then
      
      '1: Spot = t
      '2a: find length of segment
      length = Gauss(.Mutables.StdDev(TranslocationUP), .Mutables.Mean(TranslocationUP))
      If length < 1 Then length = 1
      
      If t + length > .DnaLen Then length = (.DnaLen) - t
      If t - length < 1 Then length = t - 1
      
      If length >= 1 Then
      '2b: centered at t, cut out segment of length
      ReDim tempDNA(length)
      
      'add "end" to end of temporary DNA
      tempDNA(length).tipo = 10
      tempDNA(length).value = 1
      
      second = 0
      length = length - 1
      start = t - (length - length Mod 2) \ 2
      If start < 1 Then start = 1
      
      For counter = start To t + (length - length Mod 2) \ 2 + length Mod 2
        If counter >= 1 And counter <= .DnaLen - 1 Then
          tempDNA(second) = .DNA(counter)
          .DNA(counter).tipo = 0
          .DNA(counter).value = 0
          second = second + 1
        Else
          length = length - 1
        End If
      Next counter
      'we now have the appropriate length of DNA in the temporary array.
      
      second = 0
      For counter = t + (length - length Mod 2) \ 2 + length Mod 2 + 1 To .DnaLen
        .DNA(start + second) = .DNA(counter)
        second = second + 1
        .DNA(counter).tipo = 0
        .DNA(counter).value = 0
      Next counter
      'we've closed the hole
      'the above works jsut fine
      
      'open a new hole at a random location
      second = 0
      start = fRnd(1, (.DnaLen - 1) - (length + 1))
      For counter = .DnaLen - (length + 1) To start + 1 Step -1
        .DNA(.DnaLen - second) = .DNA(counter)
        second = second + 1
        .DNA(counter).tipo = 0
        .DNA(counter).value = 0
      Next counter
      
      'Now recopy tempDNA to .DNA in new spot
      For counter = start + 1 To start + length + 1
        .DNA(counter) = tempDNA(counter - start - 1)
      Next counter
      
      'repeat
      .Mutations = .Mutations + 1
      .LastMut = .LastMut + 1
      .LastMutDetail = "Translocation moved a series " + Str(length + 1) + "long at position " + Str(t) + _
        " to position " + Str(start + 1) + " during cycle" + _
        Str(SimOpts.TotRunCycle) + vbCrLf + .LastMutDetail
      End If
    End If
  Next t
  End With
End Sub

' mutates robot colour in robot n a times
Private Sub mutatecolors(n As Integer, a As Long)
  Dim color As Long
  Dim r As Long, g As Long, b As Long
  Dim counter As Long
  
  color = rob(n).color
  
  b = color \ (65536)
  g = color \ 256 - b * 256
  r = color - b * 65536 - g * 256
  
  For counter = 1 To a
    Select Case (fRnd(1, 3))
      Case 1
        b = b + (fRnd(0, 1) * 2 - 1) * 20
      Case 2
        g = g + (fRnd(0, 1) * 2 - 1) * 20
      Case 3
        r = r + (fRnd(0, 1) * 2 - 1) * 20
    End Select
    
    If r > 255 Then r = 255
    If r < 0 Then r = 0
    
    If g > 255 Then g = 255
    If g < 0 Then g = 0
    
    If b > 255 Then b = 255
    If b < 0 Then b = 0
  Next counter
  
  rob(n).color = b * 65536 + g * 256 + r
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Public Function delgene(n As Integer, g As Integer) As Boolean
  Dim k As Integer, t As Integer
  k = CountGenes(rob(n).DNA)
  If g > 0 And g <= k Then
    DeleteSpecificGene rob(n).DNA, g
    delgene = True
    makeoccurrlist n
  End If
End Function

Public Sub DeleteSpecificGene(ByRef DNA() As block, k As Integer)
  Dim i As Long, f As Long
  
  i = genepos(DNA, k)
  If i < 0 Then Exit Sub
  f = NextStop(DNA, i)
  Delete DNA, i, f - i
End Sub

Public Sub SetDefaultMutationRates(ByRef changeme As mutationprobs)
  Dim a As Long
  With (changeme)
  
  For a = 0 To 20
    .mutarray(a) = 5000
  Next a
  
  .Mean(PointUP) = 1
  .StdDev(PointUP) = 0
  
  .Mean(DeltaUP) = 500
  .StdDev(DeltaUP) = 150
  
  .Mean(MinorDeletionUP) = 1
  .StdDev(MinorDeletionUP) = 0
  
  .Mean(InsertionUP) = 1
  .StdDev(InsertionUP) = 0
  
  .Mean(CopyErrorUP) = 1
  .StdDev(CopyErrorUP) = 0
  
  .Mean(MajorDeletionUP) = 3
  .StdDev(MajorDeletionUP) = 1
  
  .Mean(ReversalUP) = 3
  .StdDev(ReversalUP) = 1
  
  .CopyErrorWhatToChange = 80
  .PointWhatToChange = 80
  End With
End Sub
*/