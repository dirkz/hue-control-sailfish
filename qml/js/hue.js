.pragma library

.import "underscore/underscore.js" as U

var _ = U.init();

function errors(json) {
    return _.filter(_.pluck(json, 'error' ), _.identity);
}

function errorDescriptions(json) {
    return _.pluck(errors(json), 'description').join("\n");
}
