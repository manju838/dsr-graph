/*
 *    Copyright (C)2018 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"
#include <iostream>
#include <boost/format.hpp>
/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(TuplePrx tprx) : GenericWorker(tprx)
{
    connect(&autokill_timer, SIGNAL(timeout()), this, SLOT(autokill()));
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker() {
    std::cout << "Destroying SpecificWorker" << std::endl;
    G.reset();

}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params) {
    agent_name = params["agent_name"].value;
    read_file = params["read_file"].value == "true";
    write_string = params["write_string"].value == "true";
    agent_id = stoi(params["agent_id"].value);

    dsr_output_file = params["dsr_output_file"].value;
    dsr_input_file = params["dsr_input_file"].value;
    test_output_file = params["test_output_file"].value;
    dsr_input_file = params["dsr_input_file"].value;
    dsr_test_file = params["dsr_test_file"].value;
    dsr_empty_test_file = params["dsr_empty_test_file"].value;
    return true;
}

void SpecificWorker::initialize(int period) {
    std::cout << "Initialize worker" << std::endl;

    // create graph
    G = std::make_shared<CRDT::CRDTGraph>(0, agent_name, agent_id); // Init nodes
    //G->print();
    
    // GraphViewer creation
    graph_viewer = std::make_unique<DSR::GraphViewer>(G);
    mainLayout.addWidget(graph_viewer.get());
    window.setLayout(&mainLayout);
    setCentralWidget(&window);
    setWindowTitle( agent_name.c_str() );

    // qDebug() << __FUNCTION__ << "Graph Viewer started";
    

    test = std::make_shared<Test_utils>(dsrgetid_proxy);
    G_api_test = CRDT_G_api_test(test, dsr_test_file, dsr_empty_test_file );
    concurrent_test = CRDT_concurrent_test(test, 1, 1000);
    //DSR_test dst_test;
    //timer.start(300);
    //autokill_timer.start(10000);

    sleep(5);
    compute();
}

void SpecificWorker::compute()
{
    qDebug()<<"COMPUTE";
    qDebug()<<"G API TEST:";
    G_api_test.test(G);
    qDebug()<<"CONCURRENT ACCESS TEST:";
    concurrent_test.test(G);
    //test_concurrent_access(1);
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //test_create_or_remove_node(100, 10000, 10);
    // if (write_string)
    //     test_set_string(0);
    //   test_nodes_mov();
    // test_node_random();
    //int num_ops = 100000;
    //test_set_string(0, num_ops, 0);
    //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //std::string time = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    //qDebug() << __FUNCTION__ << "Elapsed time:" << QString::fromStdString(time) << "ms for " << num_ops << " ops";

    //sleep(5);
    //G->write_to_json_file(dsr_output_file);
    //exit(0);
}


void SpecificWorker::autokill()
{
    G->write_to_json_file(dsr_output_file);
    exit(0);
}

// This has to be a RPC call to the idserver component
// create and insert a new id in the list
int SpecificWorker::newID()
{
    /*static int node_counter = 5000;
    std::lock_guard<std::mutex>  lock(mut);
    created_nodos.push_back(++node_counter);
    */
    int node_id;
    try{
        node_id = dsrgetid_proxy->getID();
        created_nodos.push_back(node_id);
        qDebug()<<"New nodeID: "<<node_id;
    }catch(...)
    {
        qDebug()<<"Error getting new nodeID from idserver, check connection";
    }
    return node_id;
}

// void SpecificWorker::test_nodes_mov() {
//     static int cont = 0;
//     if (cont<LAPS) {
//         try {
//             for (auto x : G->get_list()) {
//                 for (auto &[k, v] : x.attrs) {
//                     if(k == "pos_x" || k == "pos_y") {
//                         std::string nValue = std::to_string(std::stoi(v.value) + dist(mt));
//                         cout << "Nodo: "<<x.id<<", antes: "<<v<<", ahora: "<<nValue<<endl;
//                         G->add_node_attrib(x.id, k, v.type, nValue, v.length);
//                     }
//                 }
//             }
//             std::cout<<"Working..."<<cont<<std::endl;
//             cont++;
// //            auto toDelete = randomNode(mt);
// //            std::cout<<"Deleting.... "<<toDelete<<std::endl;
// //            G->delete_node(toDelete);
//         }
//         catch (const Ice::Exception &e) {
//             std::cout << "Error reading from Laser" << e << std::endl;
//         }
//     } else if (cont == LAPS)
//     {
// //        auto to_delete = randomNode(mt);
// ////        int to_delete = 118;
// //        std::cout<<"Antes "<<to_delete<<std::endl;
// //        G->delete_node(to_delete);
// //        std::cout<<"Fin "<<std::endl;
//         cont++;
//     } else
//         std::cout<<"nada "<<std::endl;
// }

// void SpecificWorker::test_node_random()
// {   static int cont = 0;
//     if (cont<NODES) {
//         try {
//             int to_move = randomNode(mt);
//             if (G->in(to_move))
//             {
//                 std::cout << "[" << cont << "] to_move: " << to_move << std::endl;
//                 float p_x = G->get_node_attrib_by_name<float>(to_move, "pos_x");
//                 p_x += dist(mt);
//                 float p_y = G->get_node_attrib_by_name<float>(to_move, "pos_y");
//                 p_y += dist(mt);
//                 G->add_node_attrib(to_move, "pos_x", p_x);
//                 G->add_node_attrib(to_move, "pos_y", p_y);
//             }
//         } catch (const std::exception &e) {
//             std::cout << "EXCEPTION: " << __FILE__ << " " << __FUNCTION__ << ":" << __LINE__ << " " << e.what()
//                       << std::endl;
//         };
//         cont++;
//     }
// }

// void SpecificWorker::tester() {
//     try {
//         static int cont = 0, laps = 1;
//         if (laps < LAPS) {
//             try {
//                 cont++;
//                 auto test = Node{
//                         "foo_id:" + std::to_string(cont) + "_laps:" + std::to_string(laps) + "_" + agent_name, cont};
// //            std::cout <<" New node: "<< test << std::endl;
//                 G->insert_or_assign(cont, test);
//             }
//             catch (const std::exception &ex) { cerr << __FUNCTION__ << " -> " << ex.what() << std::endl; }

//             if (cont == NODES) {
//                 cont = 0;
//                 laps++;
//             }
//         } else if (laps == LAPS) {
// //            G->print();
//             laps++;
//         } else
//             sleep(5);
//     } catch(const std::exception &e){ std::cout <<__FILE__ << " " << __FUNCTION__ << " "<< e.what() << std::endl;};
// }


void SpecificWorker::write_test_output(std::string result)
{
    qDebug()<<"write results"<<QString::fromStdString(test_output_file)<<QString::fromStdString(result);
    std::ofstream out;
    out.open(test_output_file, std::ofstream::out | std::ofstream::app);
    out << result << "\n";
    out.close();
}