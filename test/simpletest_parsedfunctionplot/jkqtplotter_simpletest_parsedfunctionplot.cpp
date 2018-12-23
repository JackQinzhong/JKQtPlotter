#include <QApplication>
#include <QLineEdit>
#include "jkqtplotter/jkqtplotter.h"
#include "jkqtplotter/jkqtpgraphsparsedfunction.h"



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 1. create a window that conatins a line-edit to edit a function
    //    and a JKQtPlotter to display the function, combine everything in a layout
    QWidget mainWin;
    QLineEdit* edit=new QLineEdit(&mainWin);
    edit->setToolTip("enter a function in dependence of the variable <tt>x</tt> and press ENTER to update the graph");
    JKQtPlotter* plot=new JKQtPlotter(&mainWin);
    QVBoxLayout* layout=new QVBoxLayout;
    mainWin.setLayout(layout);
    layout->addWidget(edit);
    layout->addWidget(plot);

    // 2. now we add a JKQTPxParsedFunctionLineGraph object, which will draw the function from
    //    the line edit
    JKQTPxParsedFunctionLineGraph* parsedFunc=new JKQTPxParsedFunctionLineGraph(plot);
    plot->addGraph(parsedFunc);
    //    finally we connect the line edit with the graph, whenever RETURN is pressed,
    //    the graph is updated:
    auto updateGraphFunctor=
       [=]() {
        parsedFunc->set_title("user function: \\verb{"+edit->text()+"}");
        parsedFunc->set_function(edit->text());
        plot->update_plot();
       };
    QObject::connect(edit, &QLineEdit::returnPressed, updateGraphFunctor);
    QObject::connect(edit, &QLineEdit::editingFinished, updateGraphFunctor);
    edit->setText("sin(x*8)*exp(-x/4)");
    updateGraphFunctor();


    // 3. set some axis properties (we use LaTeX for nice equation rendering)
    plot->getXAxis()->set_axisLabel(QObject::tr("x-axis"));
    plot->getYAxis()->set_axisLabel(QObject::tr("y-axis"));


    // 4. scale the plot so the graph is contained
    plot->setXY(-10,10,-10,10);

    // show window and make it a decent size
    mainWin.show();
    mainWin.resize(600,400);

    return app.exec();
}
