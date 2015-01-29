.pragma library

.import "underscore/underscore.js" as U

var _ = U.init();

function errors(json) {
    return _.filter(_.pluck(json, 'error' ), _.identity);
}

function errorDescriptions(json) {
    return _.pluck(errors(json), 'description').join("\n");
}

function lightsList(json) {
    var buildLight = function(key) {
        var obj = json[key]
        obj.lightId = key
        return obj
    }

    var keys = _.sortBy(_.keys(json), parseInt)
    var lights = _.map(keys, buildLight)
    return lights
}

function extractSingleStateValue(json, stateName) {
    var match = new RegExp(".*" + stateName + "$")
    var objs = _.pluck(json, 'success');
    var pairs = _.map(objs, function(o) {
        return _.pairs(o)
    });
    console.log("objs", objs);
    console.log("pairs", pairs);
    var t = match.test("on");
    var matches = _.filter(objs, function(o) {
        return match.test(o)
    });
    return obj
}
