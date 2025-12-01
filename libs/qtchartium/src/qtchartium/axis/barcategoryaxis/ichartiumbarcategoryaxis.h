#pragma once



#include "src/qtchartium/axis/chartiumaxis.h"



class IChartiumBarCategoryAxis : public ChartiumAxis
{
    Q_OBJECT

public:
    explicit IChartiumBarCategoryAxis(QObject* parent = nullptr) :
        ChartiumAxis(parent)
    {
    }
    ~IChartiumBarCategoryAxis() override = default;

    IChartiumBarCategoryAxis(const IChartiumBarCategoryAxis& another)            = delete;
    IChartiumBarCategoryAxis& operator=(const IChartiumBarCategoryAxis& another) = delete;

    virtual void        append(const QStringList& categories)                           = 0;
    virtual void        append(const QString& category)                                 = 0;
    virtual void        remove(const QString& category)                                 = 0;
    virtual void        insert(int index, const QString& category)                      = 0;
    virtual void        replace(const QString& oldCategory, const QString& newCategory) = 0;
    virtual void        clear()                                                         = 0;
    virtual void        setCategories(const QStringList& categories)                    = 0;
    virtual QStringList categories()                                                    = 0;
    virtual int         count() const                                                   = 0;
    virtual QString     at(int index) const                                             = 0;

    virtual void    setMin(const QString& minCategory)                               = 0;
    virtual QString min() const                                                      = 0;
    virtual void    setMax(const QString& maxCategory)                               = 0;
    virtual QString max() const                                                      = 0;
    virtual void    setRange(const QString& minCategory, const QString& maxCategory) = 0;

    virtual void updateCategoryDomain() = 0;

signals:
    void categoriesChanged();
    void minChanged(const QString& min);
    void maxChanged(const QString& max);
    void rangeChanged(const QString& min, const QString& max);
    void countChanged();
};
