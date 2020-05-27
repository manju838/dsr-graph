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
#include <thread>

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(TuplePrx tprx) : GenericWorker(tprx) {
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker() {
    std::cout << "Destroying SpecificWorker" << std::endl;
    //G.reset();
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params) 
{

    agent_id = stoi(params["agent_id"].value);
    dsr_output_file = params["dsr_output_file"].value;
    //dsr_input_file = params["dsr_input_file"].value;
    test_output_file = params["test_output_file"].value;
    dsr_input_file = params["dsr_input_file"].value;    
    return true;
}

void SpecificWorker::initialize(int period) 
{
    std::cout << "Initialize worker" << std::endl;

    // create graph
    G = std::make_shared<CRDT::CRDTGraph>(0, agent_name, agent_id, ""); // Init nodes

     
    // Graph viewer
//	graph_viewer = std::make_unique<DSR::GraphViewer>(G);

    //initialize node combobox
    auto map = G->getCopy();
	for(const auto &[k, node] : map)
    {
        QVariant data;
        data.setValue(node);
	    this->node_cb->addItem(QString::fromStdString(node.name()), data);

        //edges
        for(const auto &[key, edge] : node.fano())
        {
            QVariant edge_data;
            edge_data.setValue(edge);
            QString from = QString::fromStdString(G->get_node(edge.from()).value().name());
            QString to = QString::fromStdString(G->get_node(edge.to()).value().name());
            QString name = from + "_" + to + "_" + QString::fromStdString(edge.type());
            this->edge_cb->addItem(name, edge_data);
        }

    }

    node_attrib_tw->setColumnCount(2);
    edge_attrib_tw->setColumnCount(2);
    QStringList horzHeaders;
    horzHeaders <<"Attribute"<< "Value";
    node_attrib_tw->setHorizontalHeaderLabels( horzHeaders );
    node_attrib_tw->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    node_attrib_tw->verticalHeader()->setDefaultSectionSize(40);


    edge_attrib_tw->setHorizontalHeaderLabels( horzHeaders );
    edge_attrib_tw->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    edge_attrib_tw->verticalHeader()->setDefaultSectionSize(40);


    connect(node_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(change_node_slot(int)));
    connect(save_node_pb, SIGNAL(clicked()), this, SLOT(save_node_slot()));
    connect(edge_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(change_edge_slot(int)));
    connect(save_edge_pb, SIGNAL(clicked()), this, SLOT(save_edge_slot()));
}


  

void SpecificWorker::compute()
{

}

void SpecificWorker::change_node_slot(int id)
{
    qDebug()<<id;
    Node node = node_cb->itemData(id).value<Node>();

    fill_table(node_attrib_tw, node.attrs());
}

void SpecificWorker::change_edge_slot(int id)
{
    Edge edge = edge_cb->itemData(id).value<Edge>();
    fill_table(edge_attrib_tw, edge.attrs());
}


void SpecificWorker::fill_table(QTableWidget *table_widget, std::map<std::string, Attrib> attribs)
{
    table_widget->setRowCount(0);
    for(auto [key, value] : attribs)
    {
        table_widget->insertRow( table_widget->rowCount() );
        table_widget->setItem(table_widget->rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(key)));
        switch (value.value()._d())
        {
            case 0:
                {
                    QLineEdit *ledit = new QLineEdit(QString::fromStdString(value.value().str()));
                    table_widget->setCellWidget(table_widget->rowCount()-1, 1, ledit);
                }
                break;
            case 1:
                {
                    QSpinBox *spin = new QSpinBox();
                    spin->setMinimum(-10000);
                    spin->setMaximum(10000);
                    spin->setValue(value.value().dec());
                    table_widget->setCellWidget(table_widget->rowCount()-1, 1, spin);
                }
                break;
            case 2:
                {
                    QDoubleSpinBox *spin = new QDoubleSpinBox();
                    spin->setMinimum(-10000);
                    spin->setMaximum(10000);
                    spin->setValue(std::round(static_cast<double>(value.value().fl()) *1000000)/ 1000000);
                    table_widget->setCellWidget(table_widget->rowCount()-1, 1, spin);
                }
                break;
            case 3:
                {
                    QWidget  *widget = new QWidget();
                    QHBoxLayout *layout = new QHBoxLayout;
                    widget->setLayout(layout);
                    if (!value.value().float_vec().empty())
                    {
                        for(std::size_t i = 0; i < value.value().float_vec().size(); ++i)
                        {
                            QDoubleSpinBox *spin = new QDoubleSpinBox();
                            spin->setMinimum(-10000);
                            spin->setMaximum(10000);
                            spin->setValue(value.value().float_vec()[i]);
                            layout->addWidget(spin);
                        }
                        table_widget->setCellWidget(table_widget->rowCount()-1, 1, widget);
                    }
                }
                break;
            case 4:
                {
                    QComboBox *combo = new QComboBox();
                    combo->addItem("true");
                    combo->addItem("false");
                    if (value.value().bl())
                        combo->setCurrentText("true");
                    else
                        combo->setCurrentText("false");
                    table_widget->setCellWidget(table_widget->rowCount()-1, 1, combo);
                }
                break;
        }
    }
    table_widget->resizeColumnsToContents();
    table_widget->horizontalHeader()->setStretchLastSection(true);
}


std::map<std::string, Attrib> SpecificWorker::get_table_content(QTableWidget *table_widget, std::map<std::string, Attrib> attrs)
{
    for (int row=0; row < table_widget->rowCount(); row++)
    {
        std::string key = table_widget->item(row, 0)->text().toStdString();
        switch(attrs[key].value()._d())
        {
            case 0:
                {
                    QLineEdit *ledit = (QLineEdit*)table_widget->cellWidget(row, 1);
                    attrs[key].value().str(ledit->text().toStdString());       
                }
                break;
            case 1:
                {
                    QSpinBox *spin = (QSpinBox*)table_widget->cellWidget(row, 1);
                    attrs[key].value().dec(spin->value());       
                }
                break;
            case 2:
                {
                    QDoubleSpinBox *spin = (QDoubleSpinBox*)table_widget->cellWidget(row, 1);
                    attrs[key].value().fl(spin->value());       
                }
                break;
            case 4:
                {
                    QComboBox *combo = (QComboBox*)table_widget->cellWidget(row, 1);
                    attrs[key].value().bl(combo->currentText().contains("true"));       
                }
                break;
            case 3:
                {
                    qDebug()<<__LINE__;
                    std::vector<float> r;
                    for (QDoubleSpinBox *spin: table_widget->cellWidget(row, 1)->findChildren<QDoubleSpinBox *>())
                    {
                        r.push_back(spin->value());
                    }
                    attrs[key].value().float_vec(r);
                    std::cout<<r;
                }
                break;                
        }       
    }
    return attrs;
}


void SpecificWorker::save_node_slot()
{
    Node node = node_cb->itemData(node_cb->currentIndex()).value<Node>();

    std::map<std::string, Attrib> new_attrs = get_table_content(node_attrib_tw, node.attrs());
    node.attrs(new_attrs);
    
    if(G->insert_or_assign_node(node))
        qDebug()<<"Node saved";
    else
    {
        qDebug()<<"Error saving node";
    }
}


void SpecificWorker::save_edge_slot()
{
    Edge edge = edge_cb->itemData(edge_cb->currentIndex()).value<Edge>();

    std::map<std::string, Attrib> new_attrs = get_table_content(edge_attrib_tw, edge.attrs());
    edge.attrs(new_attrs);
    
    if(true)//G->insert_or_assign_edge(edge))
        qDebug()<<"Edge saved";
    else
    {
        qDebug()<<"Error saving edge";
    }
  
}