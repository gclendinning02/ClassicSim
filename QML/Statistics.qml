import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Controls 2.2

Rectangle {
    id: statisticsRect
    anchors.fill: parent

    color: "transparent"

    StatisticsDamageBreakdownSorting {
        id: damageBreakdownSorting
    }

    ScrollView {
        anchors {
            top: damageBreakdownSorting.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        clip: true

        ListView {
            id: damageBreakdownTable
            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: damageBreakdownModel
            delegate: StatisticsEntryDamageBreakdown {
                name: _name
                iconurl: _icon
                totaldmgabsolute: _totaldmgabsolute
                totaldmgpercentage: _totaldmgpercent
                totalattempts: _totalattempts
                numhits: _numhits
                hitpercent: _hitpercent
                numcrits: _numcrits
                critpercent: _critpercent
                numglances: _numglances
                glancepercent: _glancepercent
                nummisses: _nummisses
                misspercent: _misspercent
                numdodges: _numdodges
                dodgepercent: _dodgepercent
                numparries: _numparries
                parrypercent: _parrypercent
            }
        }
    }

    /*
    Component.onCompleted: updateStatistics()

    Connections {
        target: statistics
        onStatisticsCleared: clearStatistics()
        onStatisticsReady: updateStatistics()
    }

    ObjectModel {
        id: objectModel
    }

    Rectangle {
        id: tmpStorage
        visible: false
    }

    function updateStatistics() {
        for (var i = 0; i < statistics.getNumStatisticsRows(); ++i) {
            var entry = root.createNewObject(tmpStorage, "StatisticEntry.qml")
            entry.imageSource = statistics.getEntryIcon(i)

            var tableInfo = statistics.getTableInfo(i)
            entry.addTable(tableInfo)

            var chartInfo = statistics.getChartInfo(i)
            if (chartInfo.length < 2)
                console.log("Malformed chart info", chartInfo)
            else if (chartInfo[1] === "PIE")
                createPieChart(chartInfo, entry)
            else
                console.log("Unhandled chart type", chartInfo[1])

            objectModel.append(entry)
        }
    }

    function clearStatistics() {
        for (var i = objectModel.count; i > 0; --i) {
            objectModel.get(i - 1).clearTable()
        }
        objectModel.clear()
    }

    function createPieChart(chartInfo, entry) {
        entry.chartTitle = chartInfo[0]

        var i = 2
        for (; i + 2 < chartInfo.length;) {
            entry.addSlice(chartInfo[i], chartInfo[i + 1], chartInfo[i + 2])
            i += 3
        }
    }

    ScrollView {
        anchors.fill: parent
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        ListView {
            clip: true
            model: objectModel
            boundsBehavior: Flickable.StopAtBounds
        }
    }*/
}
