


#ifndef PIXEL_MAPPER
#define PIXEL_MAPPER

#include <string>
#include <vector>

namespace display{

    class Pmapper{
        public:

        virtual ~Pmapper() {}

        virtual const char *getName() const = 0;

        virtual bool setParams(int chain, int parallel,
                                const char *param_string){
            return true; 
        }

        virtual bool getMappingSize(int matrix_w, int matrix_h,
                                    int *disp_w, int *disp_h)
                                    const = 0;


        virtual void mapVisibleToMat(int matrix_w, int matrix_h,
                                    int disp_x, int disp_y,
                                    int *matrix_x, int *matrix_y)
                                    const = 0;

    };

    void registerPmapper(Pmapper *pmapper);

    std::vector<std::string> getPmappers();


    const Pmapper* findPmapper(const char* name,
                                int chain, int parallel,
                                const char* param = NULL);


}

#endif // PIXEL_MAPPER#define