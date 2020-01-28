#ifndef BASICHIT_H
#define BASICHIT_H

#include <vector>

namespace pathfinder
{
/**
   class for the basic hit, it contains several constructors for easy creation

   data members are:
   - the three cartesian space coordinates
   - the associated errors as upper triangle covariance matrix
   - a flag word, whose significance still needs to done
 */
class basicHit
{
    public:
        basicHit(const basicHit&);                                                ///< copy constructor
        basicHit(double, double, double, void* = 0);                              ///< constructor; hit position is given via three doubles x,y,z
        basicHit(const std::vector<double>&, void* = 0);                          ///< constructor; hit position is given via a vector
        basicHit(const std::vector<double>&, const std::vector<double>&, void*);  ///< constructor; hit position and covariance matrix are given via a vector
        basicHit(double, double, double, const std::vector<double>&, void*);      ///< constructor; hit position is given via three doubles x,y,z; covariance matrix is given via a vector

        ///virtual destructor
        virtual ~basicHit()
        {
        }

        /// returns the x position of the hit
        double getX() const
        {
            return x;
        };

        /// returns the y position of the hit
        double getY() const
        {
            return y;
        };

        /// returns the z position of the hit
        double getZ() const
        {
            return z;
        };

        /// returns the covariance matrix of the hit
        const std::vector<double>& getCovariance() const
        {
            return covarianceMatrix;
        };

        ///returns the hit flag
        unsigned int getFlag() const
        {
            return flag;
        };

        ///\brief prints the hit position \details prints the covariance matrix (if set)
        virtual void print() const;

        ///sets the hit flag
        void setFlag(unsigned int f)
        {
            flag = f;
        };

        ///\brief Returns true if two hits are the same. \details Hits are the same if the differences of the positions of the hits to be compared is smaller than 0.001
        bool operator==(basicHit const hit) const;

        ///returns initial hit
        void* getInitialHit() const
        {
            return initialHit;
        }

    private:
        ///default constructor, disabled
        basicHit()
        {
            ;
        };         // no default constructor available

        double x/**hit x position*/, y/**hit y position*/, z/**hit z position*/;
        std::vector<double> covarianceMatrix; ///< upper triangle covariance matrix
        void* initialHit;///<initial hit
        unsigned int flag; ///< hit flag
};
}
#endif // BASICHIT_H 
