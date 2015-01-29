.pragma library

.import "underscore/underscore.js" as U

var _ = U.init();

function encloseTag(tag, s) {
    return "<" + tag + ">" + s + "</" + tag + ">";
}

function lineBreak() {
    return "<br>"
}

function hueErrors(json) {
    return _.map(json, _.identity );
}

