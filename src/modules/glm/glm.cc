#include <Module.h>

#include "samplers/LinearFactory.h"
#include "samplers/LinearGibbsFactory.h"
#include "samplers/IWLSFactory.h"
#include "samplers/HolmesHeldFactory.h"
#include "samplers/HolmesHeldBFactory.h"
#include "samplers/AlbertChibFactory.h"
#include "samplers/AlbertChibGibbsFactory.h"
#include "samplers/AMFactory.h"
#include "samplers/ConjugateFFactory.h"

using std::vector;

namespace glm {
    
    class GLMModule : public Module {
    public:
	GLMModule();
	~GLMModule();
    };
    
    GLMModule::GLMModule() 
	: Module("glm")
    {
	insert(new IWLSFactory);
	insert(new LinearGibbsFactory);
	insert(new LinearFactory);
 	insert(new AMFactory);
	insert(new AlbertChibGibbsFactory);
	insert(new AlbertChibFactory);
	insert(new HolmesHeldBFactory);
	insert(new HolmesHeldFactory);
	insert(new ConjugateFFactory);
    }
    
    GLMModule::~GLMModule() {
	
	vector<SamplerFactory*> const &svec = samplerFactories();
	for (unsigned int i = 0; i < svec.size(); ++i) {
	    delete svec[i];
	}
    }
}

glm::GLMModule _glm_module;
