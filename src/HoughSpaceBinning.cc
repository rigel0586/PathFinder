#include "HoughSpaceBinning.h"

using namespace pathfinder;

HoughSpaceBinning::HoughSpaceBinning(int _bins, double _low, double _high)
    : bins(_bins)
{
    rangelimits = std::make_pair(_low, _high);
    rangewidth = (rangelimits.second - rangelimits.first);
    binwidth = (rangewidth / (double)bins);
}

HoughSpaceBinning::HoughSpaceBinning(int _bins, std::pair<double, double> _range)
    : bins(_bins), rangelimits(_range)
{
    rangewidth = (rangelimits.second - rangelimits.first);
    binwidth = (rangewidth / (double)bins);
}

void HoughSpaceBinning::Print()
{
    std::cout << "HoughSpaceBinning Information:" << std::endl;
    std::cout << "Number of Bins: " << bins << std::endl;
    std::cout << "Range: " << rangelimits.first << " " << rangelimits.second << std::endl;
}
