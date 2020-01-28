#ifndef FINDERPARAMETER_H
#define FINDERPARAMETER_H

#include <iostream>

namespace pathfinder
{
/**
 class containing the steering parameters for track finding
 */
class FinderParameter
{
    public:
        /**
        \brief
        Constructor.
        \details
        After using this constructor either setIsStraightLine() or setIsHelix() have to be used.
        */
        FinderParameter();

        /**
           \brief
           Constructor.
           \details
           First argument is true if a straight line is to be found,
           second argument is true if a helix is to be found.
           If this constructor is used setIsStraightLine() and setIsHelix() are not needed.
         */
        FinderParameter(bool, bool);

        ///Destructor
        virtual ~FinderParameter()
        {
            ;
        };

        /*
          set FinderParameters
        */
        ///Set it to true if straight lines should be found.
        void setIsStraightLine(bool isStraightLine)
        {
            _isStraightLine = isStraightLine;
        };

        ///Set it to true if a helix should be found.
        void setIsHelix(bool isHelix)
        {
            _isHelix = isHelix;
        };

        ///\brief Set to true if a curler should be found. \details Only has an effect if a helix should be found.
        void setFindCurler(bool findCurler)
        {
            _findCurler = findCurler;
        };

        /*//not used anymore, is set via setVertex
        void setUseVertex(bool useVertex)
        {
          _useVertex = useVertex;
        };
        */

        /**
        \brief
        Set the vertex position.
        \details
        A vertex constraint is used only if a vertex position was set.
        It is only used for helices, NOT for straight lines
        */
        void setVertex(std::pair<double, double> vertex)
        {
            _VertexPosition = vertex;
            _useVertex = true;
        };

        /**
           Set to true is conformal mapping should be used.
           \todo
           This method is implemented but it does NOT deliver good track finding efficiencies.
           The reason for this is not fully understood.
           It is not recommended to use this method!
         */
        void setUseConformalMapping(bool useConformalMapping)
        {
            _useConformalMapping = useConformalMapping;
        };

	/**
	   Set to true if only intersections of functions are used for Hough space.
	 */
	void setUseIntersections(bool useIntersections)
	{
	  _useIntersections = useIntersections;
	};

        ///Set the maximum allowed distance between hit and track in xy
        void setMaxXYDistance(double maxXYDistance)
        {
            _maxXYDistance = maxXYDistance;
        };

        ///Set the maximum allowed distance between hit and track in sz
        void setMaxSZDistance(double maxSZDistance)
        {
            _maxSZDistance = maxSZDistance;
        };

        ///Set the maximum allowed distance between hit and track in xy after applying a simple fit
        void setMaxXYDistanceFit(double maxXYDistanceFit)
        {
            _maxXYDistanceFit = maxXYDistanceFit;
        };

        ///Set the maximum allowed distance between hit and track in sz after applying a simple fit
        void setMaxSZDistanceFit(double maxSZDistanceFit)
        {
            _maxSZDistanceFit = maxSZDistanceFit;
        };

        ///Set minimum number of hits needed to build a track
        void setMinimumHitNumber(unsigned int minimumHitNumber)
        {
            _minimumHitNumber = minimumHitNumber;
        };

        /**
           \brief
           Set number of bins in theta direction in the xy plane.
           \details
           The number of bins cannot exceed 1000 because three directions are saved in one integer,
           which leaves 10 bits for each direction. If a larger number is given it is set to 1000.
           \todo
           Since now the search is done in 2D only (even for circles) one could used 15 bits for each direction
           and this way increase the number of possible bins.
         */
        void setNumberXYThetaBins(unsigned int numberXYThetaBins)
        {
            if(numberXYThetaBins <= 1000)
            {
                _numberXYThetaBins = numberXYThetaBins;
            }
            else
            {
                std::cout << "WARNING: Number of bins cannot be larger than 1000!" << std::endl;
                std::cout << "Number of bins is set to 1000." << std::endl;
                _numberXYThetaBins = 1000;
            }
        };

        /**
           \brief
           Set number of bins in d0 direction in the xy plane.
           \details
           The number of bins cannot exceed 1000 because three directions are saved in one integer,
           which leaves 10 bits for each direction. If a larger number is given it is set to 1000.
           \todo
           Since now the search is done in 2D only (even for circles) one could used 15 bits for each direction
           and this way increase the number of possible bins.
         */
        void setNumberXYDzeroBins(unsigned int numberXYDzeroBins)
        {
            if(numberXYDzeroBins <= 1000)
            {
                _numberXYDzeroBins = numberXYDzeroBins;
            }
            else
            {
                std::cout << "WARNING: Number of bins cannot be larger than 1000!" << std::endl;
                std::cout << "Number of bins is set to 1000." << std::endl;
                _numberXYDzeroBins = 1000;
            }
        };

        /**
           \brief
           Set number of bins in Omega direction in the xy plane.
           \details
           The number of bins cannot exceed 1000 because three directions are saved in one integer,
           which leaves 10 bits for each direction. If a larger number is given it is set to 1000.
           \todo
           Since now the search is done in 2D only (even for circles) one could used 15 bits for each direction
           and this way increase the number of possible bins.
         */
        void setNumberXYOmegaBins(unsigned int numberXYOmegaBins)
        {
            if(numberXYOmegaBins <= 1000)
            {
                _numberXYOmegaBins = numberXYOmegaBins;
            }
            else
            {
                std::cout << "WARNING: Number of bins cannot be larger than 1000!" << std::endl;
                std::cout << "Number of bins is set to 1000." << std::endl;
                _numberXYOmegaBins = 1000;
            }
        };

        /**
           \brief
           Set number of bins in theta direction in the sz plane.
           \details
           The number of bins cannot exceed 1000 because three directions are saved in one integer,
           which leaves 10 bits for each direction. If a larger number is given it is set to 1000.
           \todo
           Since now the search is done in 2D only (even for circles) one could used 15 bits for each direction
           and this way increase the number of possible bins.
         */
        void setNumberSZThetaBins(unsigned int numberSZThetaBins)
        {
            if(numberSZThetaBins <= 1000)
            {
                _numberSZThetaBins = numberSZThetaBins;
            }
            else
            {
                std::cout << "WARNING: Number of bins cannot be larger than 1000!" << std::endl;
                std::cout << "Number of bins is set to 1000." << std::endl;
                _numberSZThetaBins = 1000;
            }
        };

        /**
           \brief
           Set number of bins in d0 direction in the sz plane.
           \details
           The number of bins cannot exceed 1000 because three directions are saved in one integer,
           which leaves 10 bits for each direction. If a larger number is given it is set to 1000.
           \todo
           Since now the search is done in 2D only (even for circles) one could used 15 bits for each direction
           and this way increase the number of possible bins.
         */
        void setNumberSZDzeroBins(unsigned int numberSZDzeroBins)
        {
            if(numberSZDzeroBins <= 1000)
            {
                _numberSZDzeroBins = numberSZDzeroBins;
            }
            else
            {
                std::cout << "WARNING: Number of bins cannot be larger than 1000!" << std::endl;
                std::cout << "Number of bins is set to 1000." << std::endl;
                _numberSZDzeroBins = 1000;
            }
        };

        /**
           \brief
           Set d0 range for xy projection.
           \details
           The range is set to -maxD - +maxD. For straighht lines and helices this are different values.
           - Straight lines: The value to be set is the maximum possible d0 that could be seen witht he detector.
           - Helices: The value to be set is the \b inverse of the maximum possible distance of the circle center to the origin.
         */
        void setMaxDxy(double maxD)
        {
            _maxDxy = maxD;
        };

        ///Set d0 range for sz projection.
        void setMaxDsz(double maxD)
        {
            _maxDsz = maxD;
        };

	///Set allowed distance between hits. Only used if _useIntersections is true.
	void setAllowedHitDistance(double dist)
	{
	  _allowedHitDistance = dist;
	};

        ///Set to true if not only the maximum in Hough space should be taken into account but also the surrounding area. \details Especially useful if small number of hits are expected on a track (order of 10).
        void setSearchNeighborhood(bool searchNeighborhood)
        {
            _searchNeighborhood = searchNeighborhood;
        };

        /**
           \brief
           Set to true if Hough space should be saved in a root file.
           \details
           For debugging use only. Hough space is saved only for the first processed event.
         */
        void setSaveRootFile(bool saveRootFile)
        {
            _saveRootFile = saveRootFile;
        };

        /*
          get FinderParameters
        */

        ///Returns true if straight line is to be found.
        bool getIsStraightLine()
        {
            return _isStraightLine;
        };

        ///Returns true if helix is to be found.
        bool getIsHelix()
        {
            return _isHelix;
        };

        ///Returns true if a curler is to be found.
        bool getFindCurler()
        {
            return _findCurler;
        };

        ///Returns true if a vertex constraint is used.
        bool getUseVertex()
        {
            return _useVertex;
        };

	///Returns true if intersections are used for Hough space
	bool getUseIntersections()
	{
	  return _useIntersections;
	};

        ///Returns the vertex position.
        std::pair<double, double> getVertex()
        {
            return _VertexPosition;
        };

        ///Returns true if conformal mapping is used.
        bool getUseConformalMapping()
        {
            return _useConformalMapping;
        };

        ///Returns the maximum allowed distance between hit and track in xy.
        double getMaxXYDistance()
        {
            return _maxXYDistance;
        };

        ///Returns the maximum allowed distance between hit and track in sz.
        double getMaxSZDistance()
        {
            return _maxSZDistance;
        };

        ///Returns the maximum allowed distance between hit and track in xy after fit.
        double getMaxXYDistanceFit()
        {
            return _maxXYDistanceFit;
        };

        ///Returns the maximum allowed distance between hit and track in sz after fit.
        double getMaxSZDistanceFit()
        {
            return _maxSZDistanceFit;
        };

        ///Returns minimum number of hits needed to build a track.
        unsigned int getMinimumHitNumber()
        {
            return _minimumHitNumber;
        };

        ///Returns number of theta bins in xy.
        unsigned int getNumberXYThetaBins()
        {
            return _numberXYThetaBins;
        };

        ///Returns number of d0 bins in xy.
        unsigned int getNumberXYDzeroBins()
        {
            return _numberXYDzeroBins;
        };

        ///Returns number of omega bins in xy.
        unsigned int getNumberXYOmegaBins()
        {
            return _numberXYOmegaBins;
        };

        ///Returns number of theta bins in sz.
        unsigned int getNumberSZThetaBins()
        {
            return _numberSZThetaBins;
        };

        ///Returns number of d0 bins in sz.
        unsigned int getNumberSZDzeroBins()
        {
            return _numberSZDzeroBins;
        };

        ///Returns xy d0 range.
        double getMaxDxy()
        {
            return _maxDxy;
        };

        ///Returns sz d0 range.
        double getMaxDsz()
        {
            return _maxDsz;
        };

	///Returns allowed distance between hits.
	double getAllowedHitDistance()
	{
	  return _allowedHitDistance;
	};

        ///Returns true if surrounding area of a maximum in Hough space should be searched.
        bool getSearchNeighborhood()
        {
            return _searchNeighborhood;
        };


        ///Returns true if Hough space should be saved in a root file.
        bool getSaveRootFile()
        {
            return _saveRootFile;
        };

        /**
          print FinderParameters
        */
        virtual void print() const;


    private:

        /*
          track type
        */
        bool _isStraightLine;///<True if a straight line should be found.
        bool _isHelix;///<True if a helix should be found.
        bool _findCurler;///<True if a curler should be found.
        bool _useVertex;///<True if a vertex constraint should be used.
        bool _useConformalMapping;///<True if conformal mapping should be used.
	bool _useIntersections;///<True if only intersections are filled in the Hough maps.

        /*
          Vertex to be used
         */
        std::pair<double, double> _VertexPosition;///<vertex position

        /*
          maximum allowed distance of hits to track
          for both projections and before and after the fit
         */
        double _maxXYDistance;///<maximum distance between hit and track in xy
        double _maxSZDistance;///<maximum distance between hit and track in sz
        double _maxXYDistanceFit;///<maximum distance between hit and track in xy after fit
        double _maxSZDistanceFit;///<maximum distance between hit and track in sz after fit

        /*
          minimum number of hits on track
        */
        unsigned int _minimumHitNumber;///<minimum number of hits to build a track

        /*
          parameters for Hough Space Size
          and
          Hough Space binning:

          - the Hough Space range for theta is always -pi ... 0

          For Straight Lines in XY:
          - need binning for theta:                                                     numberXYThetaBins
          - d0 is calculated from theta and binned afterwards:                          numberXYDzeroBins,maxDxy

          For Circles in XY: First find center of circle
          - need binning for theta:                                                     numberXYThetaBins
          - D is calculated from theta and binned afterwards:                           numberXYDzeroBins,maxDxy
          - omega is calcuulated from this and binned afterwards:                       numberXYOmegaBins

          For Straight Line in SZ
          - need binning for theta:                                                     numberSZThetaBins
          - d0 is calculated from theta and binned afterwards:                          numberSZDzeroBins,maxDsz

          (*) D is the maximum possible distance of the center of the circle to the origin of the coordinate
              system. D is d0 + R. d0 is the distance of closest approach, R the radius. R in this case needs
              to be the maximum radius a track can have so that the it can be seen as circle, not as a straight
              line. This depends on the geometry of the redout plane and must be dertermined by the user.

        */

        unsigned int _numberXYThetaBins;///<number of xy theta bins
        unsigned int _numberXYDzeroBins;///<number of xy d0/D bins
        unsigned int _numberXYOmegaBins;///<number of xy omega bins
        unsigned int _numberSZThetaBins;///<number of sz theta bins
        unsigned int _numberSZDzeroBins;///<number of xy d0 bins

        double _maxDxy;///<Hough space range in xy d0/D direction. \details Note that in case for straight lines this is the distance of closest approach and for circles it is the inverse distance of the circle center to the origin.
        double _maxDsz;///<Hough space range in sz d0 direction.

	double _allowedHitDistance;

        /*
        only needed for circles/ helices to determine Hough Space size

        How large can the radius be so that a circle is recognized as a circle and not a straight line?
        This is a rough estimation:
        R_max = (dx^2 + dy^2)
        dx = point resolution in x
        dy = (pad hight in y) * ( (number of rows) / 2 - 1)

        double _xPointResolution;
        double _yPadHight;
        double _nRows;
        */
        //

        bool _searchNeighborhood;///<True if neighborhood of a Hough space maximum should be investigated.

        bool _saveRootFile;///<True if Hough space is to be saved in a root file. \details For debugging only.

};
}
#endif //FINDERPARAMETER_H
