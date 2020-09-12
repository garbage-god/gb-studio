import flatten from "lodash/flatten";
import uniq from "lodash/uniq";
import l10n from "../helpers/l10n";

type EngineChange = {
    version: string;
    description: string;
    modifiedFiles: string[];
}

const changes: EngineChange[] = [{
    version: "2.0.0-e1",
    description: "Initial 2.0.0 engine",
    modifiedFiles: []
}, {
    version: "2.0.0-e2",
    description: "Improved music playback",
    modifiedFiles: [
        "src/core/gbt_player.s",
        "src/core/gbt_player_bank1.s"        
    ]
}];

const ejectEngineChangelog = (currentVersion: string) => {
    const startIndex = changes.findIndex((change) => change.version === currentVersion);
    let changelog = l10n("WARNING_MISSING_UPDATES") + ":\n\n";
    const modifiedFiles = [];

    for(let i=startIndex + 1; i < changes.length; i++) {
        const change = changes[i];
        changelog += `  [${change.version}]\n  ${change.description}\n\n`;
        modifiedFiles.push(change.modifiedFiles);           
    }

    changelog += "\n" + l10n("WARNING_MODIFIED_FILES") + ":\n\n  ";
    changelog += uniq(flatten(modifiedFiles)).join("\n  ")

    return changelog;
}

export default ejectEngineChangelog;
