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

    var keys = _.sortBy(_.keys(json), _.identity)
    var lights = _.map(keys, buildLight)
    return lights
}
