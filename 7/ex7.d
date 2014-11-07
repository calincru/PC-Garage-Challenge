#!/bin/rdmd
import std.range;
import std.conv;
import std.stdio;
import std.algorithm;

void main()
{
    auto fout = File("Output7.txt", "wb");
    foreach(line; File("Input7.txt").byLine)
        fout.writeln(Benzinarie(line.idup));
}

alias Benz = Tuple!(int, "cantitate", int, "nextCost");

Benz[] splitInput(string input)
{
    Benz[] ret;
    input.findSkip(`"`);
    input.findSkip(`"`);
    while (input.findSkip(`"`))
    {
        auto split = input.findSplit(`"`);
        input = split[2];
        auto numSplit = split[0].findSplit(`:`);
        ret ~= tuple(numSplit[0].to!int, numSplit[2].to!int).to!Benz;
    }
    return ret;
}

string Benzinarie(string input)
{
    auto benzinarii = splitInput(input);
    foreach (i, start; benzinarii)
    {
        auto cycleIndexes = iota(benzinarii.length).cycle();
        cycleIndexes.popFrontN(i+1);
        int curGas = start.cantitate;
        int nextCost = start.nextCost;
        foreach (iBenz; cycleIndexes)
        {
            curGas -= nextCost;
            if (curGas < 0) break;
            if (iBenz == i)
                return i.to!string;
            curGas += benzinarii[iBenz].cantitate;
            nextCost = benzinarii[iBenz].nextCost;
        }
    }
    return "Imposibil";
}

unittest
{
    writeln(Benzinarie(`["4", "3:1", "2:2", "1:2", "0:2"]`));
    writeln(Benzinarie(`["4", "3:3", "2:2", "1:2", "0:1"]`));
    writeln(Benzinarie(`["4", "3:3", "2:2", "2:2", "0:1"]`));
    writeln(Benzinarie(`["4", "3:6", "2:3", "2:2", "5:1"]`));
    writeln(Benzinarie(`"" "3:4" "3:2" "1:2" "2:2" "2:1" "3:3"`));
}
