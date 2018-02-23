 #ifndef CONSOLE_H_
 #define CONSOLE_H_

 #include <sarray/SArray.h>

 #include <vector>
 #include <iostream>
 #include <string>
 #include <map>
 #include <cstdio>
 #include <list>

 namespace jags {

 class BUGSModel;
 class ParseTree;
 struct RNG;
 class Module;

 /**
  * @short Flags for the function Console#dumpState
  */
 enum DumpType {DUMP_DATA, DUMP_PARAMETERS, DUMP_ALL};
 /**
  * @short Enumerates factory types in a model
  */
 enum FactoryType {SAMPLER_FACTORY, MONITOR_FACTORY, RNG_FACTORY};

 /**
  * @short Interface to the JAGS library
  */
 class Console
 {
   std::ostream &_out;
   std::ostream &_err;
   BUGSModel *_model;
   ParseTree *_pdata;
   ParseTree *_prelations;
   std::vector<ParseTree*> *_pvariables;
   std::vector<std::string> _array_names;
   static unsigned int &rngSeed();
 public:
   /**
    * Constructor
    *
    * @param out Output stream to which information messages will be printed.
    *
    * @param err Output stream to which error messages will be printed.
    *
    */
   Console(std::ostream &out, std::ostream &err);
   ~Console();
   /**
    * Checks syntactic correctness of model
    *
    * @param file containing BUGS-language description of the model
    *
    * @return true on success or false on error.
    */
   bool checkModel(std::FILE *file);
   /**
    * Compiles the model.
    *
    * @param data_table Map relating the names of the observed variables
    * to their values.
    *
    * @param nchain Number of chains in the model.
    *
    * @param gendata Boolean flag indicating whether the data generation
    * sub-model should be run, if there is one.
    *
    * @return true on success or false on error.
    */
   bool compile(std::map<std::string, SArray> &data_table, unsigned int nchain,
		bool gendata);
   /**
    * @short Sets the parameters (unobserved variables) of the model.  
    * 
    * This is normally done to supply initial values to the model but
    * may also be done at any point in the chain.
    *
    * @param param_table Map relating the names of the parameters to
    * their values
    *
    * @param chain Number of chain (starting from 1) to apply parameter
    * values to
    *
    * @return true on success, false on failure.
    */
   bool setParameters(std::map<std::string, SArray> const &param_table,
		      unsigned int chain);
   /**
    * Sets the name of the RNG for the given chain. The Console searches
    * through all loaded RNGFactories to find one that will generate an
    * RNG object with the given name.
    *
    * @return true on success, false on failure.
    */
   bool setRNGname(std::string const &name, unsigned int chain);
   /**
    * @short Initializes the model. 
    * 
    * Any uninitialized parameters are given values by deterministic forward
    * sampling. Then default RNGs are chosen for all chains that have not
    * already had their RNG set, based on the list of RNGFactory objects.
    * Finally, the samplers are chosen based for the unobserved
    * stochastic nodes based on the list of sampler factories.
    *
    * @returns true on success, false on failure.
    *
    * @see Model#samplerFactories, Model#rngFactories
    */
   bool initialize();
   /**
    * @short Updates the Markov chain generated by the model.
    *
    * @param n Number of iterations of the Markov chain.
    *
    * @returns true on success, false on failure.
    */ 
   bool update (unsigned int n);
   /**
    * Sets a monitor for a subset of the given node array
    *
    * @param name Name of array containing nodes to be monitored
    * 
    * @param range Range describing subset of named array to monitor.
    * A NULL range may be given, in which case, the whole array is
    * monitored.
    *
    * @param thin Thinning interval for the monitor
    *
    * @param type Name of the monitor type.
    *
    */
   bool setMonitor(std::string const &name, Range const &range,
		   unsigned int thin, std::string const &type); 
   /**
    * @short Clears a monitor. 
    * 
    * The arguments name, range and type must correspond exactly to
    * a previous call to setMonitor.
    */
   bool clearMonitor(std::string const &name, Range const &range,
		     std::string const &type);
   /**
    * @short Dumps the state of the model.
    *
    * Writes the current values of the variables to the data table.
    *
    * @param data_table Data table to receive values. This must be
    * initially empty.
    *
    * @param rng_name String which will be overwritten with the name
    * of the RNG for this chain.
    *
    * @param type Flag describing which values in the model to dump. 
    * DUMP_DATA dumps the observed stochastic nodes, DUMP_PARAMETERS
    * dumps the unobserved stochastic nodes, and DUMP_ALL, dumps the values
    * of all named nodes in the model.
    *
    * @param chain Number of the chain for which to dump values (starting
    * from 1). 
    */
   bool dumpState(std::map<std::string,SArray> &data_table, 
		  std::string &rng_name,
		  DumpType type, unsigned int chain);
   /**
    * Returns the iteration number of the model.
    */
   unsigned int iter() const;
   /**
    * Returns a vector of variable names used by the model. This vector
    * excludes any counters used by the model within a for loop.
    */
   std::vector<std::string> const &variableNames() const;
   /**
    * Retrieves the names of observed stochastic nodes
    *
    * These names are guaranteed to correspond to the values given by 
    * deviance monitors in the DIC module
    */
   std::vector<std::string> const &observedStochasticNodeNames() const;
   /**
    * Dump the contants of monitored node in CODA format
    *
    * @param node Vector of monitored nodes to be dumped, each node
    * is described by the variable name and index range. If the vector
    * is empty then ALL monitored nodes will be dumped.
    * 
    * @param prefix Prefix to be prepended to the output file names
    */
   bool coda(std::vector<std::pair<std::string, Range> > const &nodes,
	     std::string const &prefix);
   bool coda(std::string const &prefix);
   BUGSModel const *model();
   unsigned int nchain() const;
   bool dumpMonitors(std::map<std::string,SArray> &data_table,
		     std::string const &type, bool flat);
   bool dumpSamplers(std::vector<std::vector<std::string> > &sampler_list);
   /** Turns off adaptive mode of the model */
   bool adaptOff();
   /** Checks whether adaptation is complete */
   bool checkAdaptation(bool &status);
   /** Indicates whether model is in adaptive mode */
   bool isAdapting() const;
   /** Clears the model */
   void clearModel();
   /**
    * Loads a module by name
    */
   static bool loadModule(std::string const &name);
   /**
    * Unloads a module by name
    */ 
   static bool unloadModule(std::string const &name);
   /**
    * Returns a vector containing the names of loaded modules
    */
   static std::vector<std::string> listModules();
   /**
    * Returns a vector containing the names of currently loaded factories
    * and whether or not they are active.
    */
   static std::vector<std::pair<std::string, bool> >  
       listFactories(FactoryType type);
   /**
    * Sets a factory to be active or inactive
    */
   static bool setFactoryActive(std::string const &name, FactoryType type, 
				bool active);
   /**
    * Sets the seed for all RNG factories.
    *
    * Sets the seed for all currently loaded RNGFactory objects,
    * including the ones that are currently active. After a call to
    * setSeed, all RNGFactory objects in subsequently loaded Modules
    * will have their seeds set to the given value. 
    *
    * @param seed Unsigned integer giving a random seed. The seed must
    * be positive: a zero seed will have no effect.
    *
    * @see RNGFactory#setSeed
    */
   static void setRNGSeed(unsigned int seed);
};

} /* namespace jags */

#endif /* CONSOLE_H_ */
