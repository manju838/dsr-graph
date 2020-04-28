#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>
#include "../../../graph-related-classes/CRDT.h"
#include "../../../graph-related-classes/CRDT_graphviewer.h"
//#include "../../../graph-related-classes/libs/DSRGraph.h"
#include <random>
#include <thread>
#include <chrono>


#define LAPS 50
#define NODES 1500
#define TIMEOUT 5

class SpecificWorker : public GenericWorker
{
	Q_OBJECT
	public:
		SpecificWorker(TuplePrx tprx);
		~SpecificWorker();
		bool setParams(RoboCompCommonBehavior::ParameterList params);
		std::shared_ptr<CRDT::CRDTGraph> getGCRDT() const {return G;};

	public slots:
		void compute();
		void initialize(int period);

	signals:
		void addNodeSIGNAL(std::int32_t id, const std::string &name, const std::string &type, float posx, float posy, const std::string &color);
		void addEdgeSIGNAL(std::int32_t from, std::int32_t to, const std::string &ege_tag);

	private:
		InnerModel *innerModel;
		std::string agent_name;
		bool read_file;
		bool write_string;
		int agent_id;
		std::shared_ptr<CRDT::CRDTGraph> G;
		std::unique_ptr<DSR::GraphViewer> graph_viewer;

		// Tests
		//void tester();
		//void test_nodes_mov();
		void test_set_string(int i);
		void test_create_or_remove_node(int i);
		void test_create_or_remove_edge(int i);
		void test_concurrent_access(int num_threads);


		void write_test_output(std::string result);
		std::string results_file;
		std::string MARKER = ";";

		//void test_node_random();
		// Random
		std::random_device rd;
		std::mt19937 mt;
		std::uniform_real_distribution<float> dist;
        std::uniform_int_distribution<int> randomNode, random_selector, node_selector;

		//threadss
		std::vector<std::thread> threads;
		std::vector<int> created_nodos;
        std::vector<std::pair<int, int>> created_edges;

        pair<int, int> removeEdge();

        int newID();
		int removeID();
        int getID();
		std::mutex mut;
		
};

#endif
