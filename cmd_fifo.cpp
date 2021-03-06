#include <QDebug>
#include <QRegExp>

#include <unistd.h>
#include <fcntl.h>

#include <errno.h>
#include <linux/input.h>

#include "cmd_fifo.h"
//#include <assert>

//static const int max_fifo_input_size = 32;

cmdFifo::cmdFifo(const QString _fifoPath):
m_fifoFile(_fifoPath)
{}

cmdFifo::~cmdFifo()
{
  closeFifo();
}

void cmdFifo::openFifo()
{
  if(!(m_fifoFile.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Unbuffered|QIODevice::Text)))
  {
    qDebug() << m_fifoFile.fileName() << ": fifo open failed";
    return;
  }

//  qDebug() << "Cmd fifo opened successfully";
  emit opened();
}

void cmdFifo::closeFifo()
{
  m_fifoFile.close();

  emit closed();
}

void cmdFifo::writeFifo(QString _cmd)
{
    m_fifoFile.write(_cmd.toLocal8Bit().data());
    m_fifoFile.flush();
}

