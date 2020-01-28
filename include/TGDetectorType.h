#ifndef TGDETECTORTYPE_H
#define TGDETECTORTYPE_H

namespace pathfinder
{
/**
   This class is needed by the track generator. It contains the range of the detector in x,y,z as well as the size of pads in y, which corresponds to the row height. Only rectangular layouts are taken into account.
*/
class TGDetectorType
{
    public:
        /**
        Constructor. The parameters are the minimum and maximum x, the minimum and maximum y and the minimum and maximum z of the detector. The last parameter gives the height of a measurement row.
             */
        TGDetectorType(double _padplaneXmin,
                       double _padplaneXmax,
                       double _padplaneYmin,
                       double _padplaneYmax,
                       double _padplaneZmin,
                       double _padplaneZmax,
                       double _padsizeY)
            : padplaneXmin(_padplaneXmin), padplaneXmax(_padplaneXmax),
              padplaneYmin(_padplaneYmin), padplaneYmax(_padplaneYmax),
              padplaneZmin(_padplaneZmin), padplaneZmax(_padplaneZmax), padsizeY(_padsizeY)
        {
            ;
        };

        /**
        Destructor.
             */
        ~TGDetectorType()
        {
            ;
        };

        ///returns minimum x of detector
        double getPadPlaneXmin()
        {
            return padplaneXmin;
        };

        ///returns maximum x of detector
        double getPadPlaneXmax()
        {
            return padplaneXmax;
        };

        ///returns minimum y of detector
        double getPadPlaneYmin()
        {
            return padplaneYmin;
        };

        ///returns maximum y of detector
        double getPadPlaneYmax()
        {
            return padplaneYmax;
        };

        ///returns minimum z of detector
        double getPadPlaneZmin()
        {
            return padplaneZmin;
        };

        ///returns maximum z of detector
        double getPadPlaneZmax()
        {
            return padplaneZmax;
        };

        ///returns height of a measurement row
        double getPadSizeY()
        {
            return padsizeY;
        };
    private:
        ///default constructor, disabled
        TGDetectorType()
        {
            ;
        };
        double padplaneXmin;///<minimum x of detector
        double padplaneXmax;///<maximum x of detector
        double padplaneYmin;///<minimum y of detector
        double padplaneYmax;///<maximum y of detector
        double padplaneZmin;///<minimum z of detector
        double padplaneZmax;///<maximum z of detector
        double padsizeY;///<height of measurement row
};
}
#endif //TGDETECTORTYPE_H
